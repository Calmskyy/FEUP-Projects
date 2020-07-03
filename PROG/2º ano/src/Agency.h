#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "Utilities.h"
#include "Address.h"
#include "Client.h"
#include "Packet.h"

using namespace std;

class Agency {
private:
	string name; // name of the  agency
	unsigned int VATnumber; // VAT number of the agency
	Address address; // address of the agency
	string URL; // URL of the agency Web site
	vector<Client> clients; // vector to store the existing clients
	vector<Packet> packets; // vector to store the existing packets

	string agencyFileName; // name of the file that stores agency details
	string clientsFileName; // name of the file that stores client details
	string packetsFileName; // name of the file that stores packet details

	bool clientsInfoHasChanged; // flag that is set to "true" if at least one client has been changed/added/deleted
	bool agencyInfoHasChanged; // flag that is set to "true" if at least one agency attribute has been changed/added/deleted
	bool packetsInfoHasChanged; // flag that is set to "true" if at least one packet has been changed/added/deleted
	unsigned maxClientsId; // maximum value among all clients identifiers
	unsigned maxPacketsId; // maximum value among all packets identifiers

public:
	Agency(string fileName);

	// methods GET
	string getName() const;
	unsigned getVATnumber() const;
	Address getAddress() const;
	string getURL() const;
	vector<Client> getClients() const;
	vector<Packet> getPackets() const;
	string getAgencyFileName() const;
	string getClientsFileName() const;
	string getPacketsFileName() const;
	bool getClientsInfoHasChanged() const;
	bool getPacketsInfoHasChanged() const;
	bool getAgencyInfoHasChanged() const;
	unsigned getMaxClientsId() const;
	unsigned getMaxPacketsId() const;

	// methods SET
	void setName(string name);
	void setVATnumber(unsigned VATnumber);
	void setAddress(Address address);
	void setURL(string URL);
	void setClients(vector<Client> & clients);
	void setPackets(vector<Packet> & packets);
	void setClientsInfoHasChanged(bool clientsInfoHasChanged);
	void setPacketsInfoHasChanged(bool packetsInfoHasChanged);
	void setAgencyInfoHasChanged(bool agencyInfoHasChanged);

	// other methods */

	friend ostream& operator<<(ostream& out, const Agency & agency); // displays the agency's information
	void sortPackets(); // copies the packets' info to the clients that have bought them
	void removeClient(int chosenClient); // removes a client from the database
	void addClient(); // adds a client to the database
	void removePacket(int chosenPacket); // makes a packet unavailable
	void addPacket(); // adds a packet to the database
	vector<Packet> viewSameDestinationPackets(const string destination, int printOption); // view packets with the same destination
	void viewBetweenDatePackets(const vector<Packet> &packets); // view packets between 2 dates
	void viewBetweenDateSameDestinationPackets(const string destination); // view packets between 2 dates, with the same destination
	void viewAllClientsPackets(); // view all clients' bought packets
	void viewTotalPurchasedPackets(); // view all packets purchased and their income
	vector<string> viewMostVisitedLocations(int printOption, unsigned int &N); // view the N most visited locations, in descending order
	void viewSuggestedPacksToClients(unsigned int &N); // recommend a new packet, based on the N most visited ones

private:
	vector<Client> loadClients(string fileName); // loads information in the clients file
	vector<Packet> loadPackets(string fileName); // loads information in the packets file
};
