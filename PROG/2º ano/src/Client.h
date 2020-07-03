#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Utilities.h"
#include "Packet.h"
#include "Address.h"

using namespace std;

class Client {
private:
	string name; // name of the client
	unsigned int VATnumber; // VAT number of client
	unsigned short familySize;  // number of family members
	Address address; // client's address
	vector<Packet> packets; // vector to store client's packets bought
	unsigned totalPurchased; // total value spent by the client

public:
	Client();

	// GET methods

	string getName() const;
	unsigned int getVATnumber() const;
	unsigned short getFamilySize() const;
	Address getAddress() const;
	vector<Packet> getPacketList() const;
	unsigned getTotalPurchased() const;

	// SET methods

	void setName(string name);
	void setVATnumber(unsigned int VATnumber);
	void setFamilySize(unsigned short familySize);
	void setAddress(Address address);
	void setPacketList(vector<Packet> & packets);
	void setTotalPurchased(unsigned totalPurchased);

	// other methods

	friend ostream& operator<<(ostream& out, const Client & client); // displays the client's information
	int purchasePacket(vector<Packet> &packets); // purchase a packet
	unsigned changeClient(); // change the client's attributes
	void refundPacket(int chosenPacket, vector<Packet> &packets); // refund a packet
	void viewClientPackets(const vector<Packet> &packets); // view this client's packets
};
