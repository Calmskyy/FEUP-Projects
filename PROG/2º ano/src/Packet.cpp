#include "Packet.h"

Packet::Packet() {
	unavailable = false;
}

// metodos GET

int Packet::getId() const {

	return id;
}

string Packet::getMainDestination() const
{
	return mainDestination;
}

vector<string> Packet::getSecondaryDestinations() const
{
	return secondaryDestinations;
}

Date Packet::getBeginDate() const {

	return begin;
}

Date Packet::getEndDate() const {

	return end;
}

double Packet::getPricePerPerson() const {

	return pricePerPerson;
}

unsigned Packet::getMaxPersons() const {

	return maxPersons;
}

unsigned Packet::getSpotsSold() const {

	return spotsSold;
}

bool Packet::getUnavailable() const {

	return unavailable;
}

// metodos SET

void Packet::setId(int id) {

	this->id = id;
}

void Packet::setMainDestination(string mainDestination) {

	this->mainDestination = mainDestination;
}

void Packet::setSecondaryDestinations(vector<string> secondaryDestinations) {

	this->secondaryDestinations = secondaryDestinations;
}

void Packet::setBeginDate(Date begin) {

	this->begin = begin;
}

void Packet::setEndDate(Date end) {

	this->end = end;
}

void Packet::setPricePerPerson(double pricePerPerson) {

	this->pricePerPerson = pricePerPerson;
}

void Packet::setMaxPersons(unsigned maxPersons) {

	this->maxPersons = maxPersons;
}

void Packet::setSpotsSold(unsigned spotsSold) {

	this->spotsSold = spotsSold;
}

void Packet::setUnavailable(bool unavailable) {

	this->unavailable = unavailable;
}

void Packet::readAndSetSecondaryDestinations(string secondaryDestinationString) {
	char delim = ',';
	size_t pos = 0;
	size_t temp_pos = 0;
	string data;

	if (secondaryDestinationString == "") { // if empty string, empty the vector
		secondaryDestinations.clear();
		return;
	}

	while (1) {
		pos = secondaryDestinationString.find(delim, temp_pos);
		if (pos == npos) {
			data = secondaryDestinationString.substr(temp_pos, secondaryDestinationString.length() - pos);
			if (data != "")
				secondaryDestinations.push_back(data);
			break;
		}
		data = secondaryDestinationString.substr(temp_pos, pos - temp_pos);
		temp_pos = pos + 2;
		secondaryDestinations.push_back(data); // copy everything separated between a comma + a space
	}
}

void Packet::updateIdentifier() {

	if (unavailable == true) {
		if (id > 0)
			id = -id;
		return;
	}

	if (spotsSold == maxPersons)
		if (id > 0)
			id = -id;

	if (spotsSold < maxPersons)
		if (id < 0)
			id = -id;
}

unsigned Packet::changePacket() {

	cout << "What do you want to change? (input corresponding number)" << endl;
	cout << "Destinations (1), Start date (2), End date (3), price (4), Max amount of people (5) (type 0 at any time to cancel)" << endl;

	int option = readInputNumber(0, 5);
	string input;
	unsigned int number;
	bool dateCheck;
	string mainDestinationString;
	string secondaryDestinationString;
	Date newBegin, newEnd;

	cin.clear();
	cin.ignore(200, '\n');

	switch (option) {
	case 0:
		return 1;
	case 1:
		cout << "Current main destination: " << mainDestination << endl;
		cout << "Input new main destination: ";
		getline(cin, input);
		if (input.length() == 1 && input[0] == '0')
			return 1;
		mainDestinationString = input;

		if (secondaryDestinations.size() == 0) {
			cout << "There are no secondary destinations currently." << endl;
			cout << "Input the secondary destinations you wish to add (or type 1 if you do not wish to add any)" << endl;
			cout << "Each destination must be separated by a comma and a space (x, y): " << endl;
			getline(cin, input);
			if (input.length() == 1 && input[0] == '0')
				return 1;
			else if (input.length() == 1 && input[0] == '1')
				secondaryDestinationString = ""; // clear the secondary destinations
			else
				secondaryDestinationString = input;
		}
		else {
			cout << "Current secondary destinations: ";
			for (unsigned int i = 0; i < secondaryDestinations.size(); i++) {
				if (i == secondaryDestinations.size() - 1) {
					cout << secondaryDestinations.at(i);
					break;
				}
				cout << secondaryDestinations.at(i) << ", ";
			}
			cout << "Input new secondary destinations (type 1 if you wish to remove them)" << endl;
			cout << "Each destination must be separated by a comma and a space (x, y): " << endl;
			getline(cin, input);
			if (input.length() == 1 && input[0] == '0')
				return 1;
			else if (input.length() == 1 && input[0] == '1')
				secondaryDestinationString = "";
			else
				secondaryDestinationString = input;
		}
		cout << "Destinations changed successfully." << endl;
		mainDestination = mainDestinationString;
		readAndSetSecondaryDestinations(secondaryDestinationString);
		break;
	case 2:
		cout << "Current start date: " << begin << endl;
		cout << "Current end date: " << end << endl;
		while (1) {

			cout << "Input new start date - year: ";
			newBegin.setYear(readInputNumber());
			if (newBegin.getYear() == 0)
				return 1;
			cout << "Input new start date - month: ";
			newBegin.setMonth(readInputNumber());
			if (newBegin.getMonth() == 0)
				return 1;
			cout << "Input new start date - day: ";
			newBegin.setDay(readInputNumber());
			if (newBegin.getDay() == 0)
				return 1;
			if (newBegin.checkValidYear() == false) {
				cout << "Year is invalid! Please input a year between 2019 and 2030." << endl;
				continue;
			}
			if (newBegin.checkValidMonth() == false) {
				cout << "Month is invalid! Please input a month between 1 and 12." << endl;
				continue;
			}
			if (newBegin.checkValidDay() == false) {
				cout << "Day is invalid! Please input a valid day (depends on the chosen month)." << endl;
				continue;
			}
			dateCheck = newBegin.checkOrderDates(end); // check if the first date comes before the second
			if (dateCheck == true)
				break;
			else {
				cout << "End date should come after the start date! Change the start date to one that comes before: " << endl;
			}
		}
		begin = newBegin;
		cout << "Start date changed successfully." << endl;
		break;
	case 3:
		cout << "Current start date: " << begin << endl;
		cout << "Current end date: " << end << endl;
		while (1) {

			cout << "Input new end date - year: ";
			newEnd.setYear(readInputNumber());
			if (newEnd.getYear() == 0)
				return 1;
			cout << "Input new end date - month: ";
			newEnd.setMonth(readInputNumber());
			if (newEnd.getMonth() == 0)
				return 1;
			cout << "Input new end date - day: ";
			newEnd.setDay(readInputNumber());
			if (newEnd.getDay() == 0)
				return 1;
			if (newEnd.checkValidYear() == false) {
				cout << "Year is invalid! Please input a year between 2019 and 2030." << endl;
				continue;
			}
			if (newEnd.checkValidMonth() == false) {
				cout << "Month is invalid! Please input a month between 1 and 12." << endl;
				continue;
			}
			if (newEnd.checkValidDay() == false) {
				cout << "Day is invalid! Please input a valid day (depends on the chosen month)." << endl;
				continue;
			}
			dateCheck = begin.checkOrderDates(newEnd);
			if (dateCheck == true)
				break;
			else {
				cout << "Start date should come before the end date! Change the end date to one that comes after: " << endl;
			}
		}
		end = newEnd;
		cout << "End date changed successfully." << endl;
		break;
	case 4:
		double newPrice;
		cout << "Current price: " << pricePerPerson << endl;
		cout << "Input new price: ";
		newPrice = readDoubleInputNumber(0, 2000);
		if (newPrice == 0)
			return 1;
		pricePerPerson = newPrice;
		cout << "Price changed successfully." << endl;
		break;
	case 5:
		cout << "Current max amount of people: " << maxPersons << endl;
		cout << "Input new amount: ";
		while (1) {
			number = readInputNumber();
			if (number == 0)
				return 1;
			if (number < spotsSold) { // check for conflict with people's purchases
				cout << "New amount of max people is less than packs sold, try again: ";
				continue;
			}
			break;
		}
		maxPersons = number;
		updateIdentifier();
		cout << "Max amount of people changed successfully." << endl;
		break;
	}

	cout << "Travel pack changed successfully." << endl;
	return 0;
}

void Packet::copyPacket(Packet packet) {

	this->id = packet.getId();
	this->mainDestination = packet.getMainDestination();
	this->secondaryDestinations = packet.getSecondaryDestinations();
	this->begin = packet.getBeginDate();
	this->end = packet.getEndDate();
	this->pricePerPerson = packet.getPricePerPerson();
	this->maxPersons = packet.getMaxPersons();
	this->spotsSold = packet.getSpotsSold();
}

ostream& operator<<(ostream& out, const Packet & packet) {

	out << "===========================" << endl;
	out << "Identifier: " << packet.id << endl;
	if (packet.secondaryDestinations.size() != 0) {
		out << "Destinations: " << packet.mainDestination << " - ";
		for (unsigned int i = 0; i < packet.secondaryDestinations.size(); i++) {
			if (i == packet.secondaryDestinations.size() - 1) {
				out << packet.secondaryDestinations.at(i);
				break;
			}
			out << packet.secondaryDestinations.at(i) << ", ";
		}
		cout << endl;
	}
	else
		out << "Destination: " << packet.mainDestination << endl;
	out << "Start date: " << packet.begin << endl;
	out << "End date: " << packet.end << endl;
	out << "Price: " << packet.pricePerPerson << endl;
	out << "Max amount of people: " << packet.maxPersons << endl;
	out << "Sold spots: " << packet.spotsSold << endl;
	out << "===========================" << endl;
	return out;
}
