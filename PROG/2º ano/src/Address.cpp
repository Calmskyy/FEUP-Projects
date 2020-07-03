#include "Address.h"

Address::Address() {
}

Address::Address(string fileLine) {

	Address address;

	char delim = '/';
	size_t pos = 0;
	size_t temp_pos = 0;
	string data;
	int count = 0;

	while (count < 5) {

		pos = fileLine.find(delim, temp_pos);
		data = fileLine.substr(temp_pos, pos - 1 - temp_pos);
		temp_pos = pos + 2;

		switch (count) {
		case 0:
			street = data;
			break;
		case 1:
			doorNumber = (unsigned short)stoi(data, nullptr, 0);
			break;
		case 2:
			floor = data;
			break;
		case 3:
			postalCode = data;
			break;
		case 4:
			location = data;
			break;
		default:
			break;
		}
		count++;
	}
}

// GET methods

string Address::getStreet() const {

	return street;
}

unsigned short Address::getDoorNumber() const {

	return doorNumber;
}

string Address::getFloor() const {

	return floor;
}

string Address::getPostalCode() const {

	return postalCode;
}

string Address::getLocation() const {

	return location;
}


// SET methods

void Address::setStreet(string street) {

	this->street = street;
}

void Address::setDoorNumber(unsigned short doorNumber) {

	this->doorNumber = doorNumber;
}

void Address::setFloor(string floor) {

	this->floor = floor;
}

void Address::setPostalCode(string postalCode) {

	this->postalCode = postalCode;
}

void Address::setLocation(string  location) {

	this->location = location;
}

ostream& operator<<(ostream& out, const Address & address) {

	out << "  Address - { " << "Street name: " << address.street << " }" << endl;
	out << "  Address - { " << "Door number: " << address.doorNumber << " }" << endl;
	out << "  Address - { " << "Floor number: " << address.floor << " }" << endl;
	out << "  Address - { " << "Zip code: " << address.postalCode << " }" << endl;
	out << "  Address - { " << "Locale: " << address.location << " }";
	return out;
}
