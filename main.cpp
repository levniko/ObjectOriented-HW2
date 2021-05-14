/*
Name : Muhammet Aslan
Number : 150160031
Instructor : Gülþen Eryiðit
Date : 04.05.2020
*/

#include <iostream>
#include <string>
using namespace std;


class Person {
private:
	string name, surname;
public:
	Person() {
		//	cout << "Person contsructer"<< endl;
	}
	Person(string name, string surname) { // Constructor
		this->name = name;
		this->surname = surname;
	}
	void setName(string n) { name = n; };
	void setSurname(string s) { surname = s; };
	string getName() { return name; }
	string getSurname() { return surname; }

};

class Owner : public Person {
private:
	double ownership;
public:
	Owner() {
		//	cout << "Owner constructer called"<< endl;
	}
	Owner(string name, string surname) :Person(name, surname) { // Constructor
	}
	void setOwnership(double ow) { this->ownership = ow; };
	double getOwnership() const { return this->ownership; };
};

class Courier : public Person {
private:
	string vehicle;
	int capacity;
public:
	Courier() {
		//	cout<<" Courier constructer called"<< endl;
	}

	Courier(string name, string surname, string vehicle) :Person(name, surname) {
		// Constructor
		this->vehicle = vehicle;
		if (vehicle == "car") {
			this->capacity = 200;
		}
		else if (vehicle == "motorcycle") {
			this->capacity = 35;
		}
		else if (vehicle == "bicycle") {
			this->capacity = 10;
		}
		else {

			cout << "Invalid vehicle" << endl;

		}

	}
	int getCapacity() const {
		return this->capacity;
	}
};

class Business {
private:
	string name, address;
	Owner* owner_arr;
	int number_of_owners;
	Courier courier_arr[10000];
	int number_of_courier = 0;

public:



	Business(string n, string a, Owner* o, int x) { //Constructor

		name = n;
		address = a;
		number_of_owners = x;

		owner_arr = new Owner[100000];
		for (int i = 0; i < x; i++) {

			owner_arr[i] = *(new Owner(o[i].getName(), o[i].getSurname()));
		}

		for (int i = 0; i < x; i++) {
			//	cout << " Giriyomu buraya acaba"<< endl;
			this->owner_arr[i].setOwnership(100 / x);
		}
	}
	~Business() {
		delete[] owner_arr;

	}
	string getName() const { return name; }
	string getAddress() const { return address; }

	void hire_courier(Courier c) {
		courier_arr[number_of_courier] = c;
		number_of_courier++;
	};

	void deleteElementt(Courier arr[], int n, int i) // Delete an element from array
	{
		if (i < n)
		{
			
			n = n - 1;
			for (int j = i; j < n; j++)
				arr[j] = arr[j + 1];
		}
	};
	void fire_courier(Courier c) {
		bool isFound = false;
		int foundIndex = 0;
		for (int i = 0; i < number_of_courier; i++) {
			if (courier_arr[i].getSurname() == c.getSurname()) {

				this->deleteElementt(courier_arr, number_of_courier, foundIndex);
				number_of_courier--;
				isFound = true;
			}
			foundIndex++;
		}
		if (isFound == false) {
			cout << "Error finding the courier";
		}

	};

	void list_couriers() { // Cout couriers

		for (int i = 0; i < number_of_courier; i++) {
			
			cout << "" << courier_arr[i].getName() << " " << courier_arr[i].getSurname() << endl;
		}
	};

	void list_owners() { // Cout owners

		for (int i = 0; i < 2; i++) {

			cout << "" << owner_arr[i].getName() << " " << owner_arr[i].getSurname() << endl;

		}

	};

	int calculate_shipment_capacity() { //Shipment capacity method

		int shipment_capacity = 0;
		for (int i = 0; i < number_of_courier; i++) {
			shipment_capacity += this->courier_arr[i].getCapacity();
		}
		return shipment_capacity;
	}
	void operator() ()  // () operator overload
	{
		cout << "" << getName() << " " << getAddress() << endl;
		Business::list_couriers();
		Business::list_owners();

	};


	Courier operator[] (int a)  // [] operator overload
	{
		return courier_arr[a];
	};

};

int main() {
	// Create owners of the business
	//Constructor parameters: name, surname
	Owner o1 = Owner("Owner_name1", "surname1");
	Owner o2 = Owner("Owner_name2", "surname2");
	Owner* owner_arr = new Owner[2];
	owner_arr[0] = o1;
	owner_arr[1] = o2;

	//Crete the business itself
	//Constructor parameters: name, address, owner_array, number_of_owners
	Business atlas = Business("Atlas", "Maslak Istanbul/Turkey", owner_arr, 2);

	// Print owner info to screen: name, surname, ownership
	atlas.list_owners();
	
		// Add new employees
		// Constructor parameters: name, surname, vehicle_type
	Courier c1 = Courier("Courier", "surname1", "car");
	Courier c2 = Courier("Courier", "surname2", "motorcycle");
	Courier c3 = Courier("Courier", "surname3", "motorcycle");

	atlas.hire_courier(c1);
	atlas.hire_courier(c2);
	atlas.hire_courier(c3);


	// Print business info to screen
	// Name, address, owners, couriers

	atlas();

	// Get courier with index 1 and remove it from the list/array
	Courier cour = atlas[1];
	atlas.fire_courier(cour);

	// Print remaining couriers
	atlas.list_couriers();

	// Print current maximum shipment capacity
	std::cout << atlas.calculate_shipment_capacity() << std::endl;
	return 0;
}
