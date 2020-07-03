#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Date.h"
#include "Utilities.h"

using namespace std;

class Packet {
private:
	int id; // packet unique identifier
	string mainDestination; // main destination to visit
	vector<string> secondaryDestinations; // secondary destinations to visit
	Date begin;  // begin date
	Date end;  // end date
	double pricePerPerson; // price per person
	unsigned maxPersons; // max number of people to sell the pack to
	unsigned spotsSold; // number of spots already reserved
	bool unavailable; // if the packet was manually removed

public:
	Packet();

	// GET methods
	int getId() const;
	string getMainDestination() const;
	vector<string> getSecondaryDestinations() const;
	Date getBeginDate() const;
	Date getEndDate() const;
	double getPricePerPerson() const;
	unsigned getMaxPersons() const;
	unsigned getSpotsSold() const;
	bool getUnavailable() const;

	// SET methods
	void setId(int id);  // to set negatve if "deprecated"
	void setMainDestination(string mainDestination);
	void setSecondaryDestinations(vector<string> secondaryDestinations);
	void setBeginDate(Date begin);
	void setEndDate(Date end);
	void setPricePerPerson(double pricePerPerson);
	void setMaxPersons(unsigned maxPersons);
	void setSpotsSold(unsigned spotsSold);
	void setUnavailable(bool unavailable);

	// other methods

	friend ostream& operator<<(ostream& out, const Packet & packet); // display a packet's information
	void readAndSetSecondaryDestinations(string secondaryDestinationString); // transform a string into a vector of destinations
	void updateIdentifier(); // change the identifier if necessary
	unsigned changePacket(); // change the packet's attributes
	void copyPacket(Packet packet); // copy a packet's content to another
};
