#include "Client.h"

Client::Client() {
}

// GET methods

string Client::getName() const {

	return name;
}

unsigned int Client::getVATnumber() const {

	return VATnumber;
}

unsigned short Client::getFamilySize() const {

	return familySize;
}

Address Client::getAddress() const {

	return address;
}

vector<Packet> Client::getPacketList() const {

	return packets;
}

unsigned Client::getTotalPurchased() const {

	return totalPurchased;
}

// metodos SET

void Client::setName(string name) {

	this->name = name;
}

void Client::setVATnumber(unsigned int VATnumber) {

	this->VATnumber = VATnumber;
}

void Client::setFamilySize(unsigned short familySize) {

	this->familySize = familySize;
}

void Client::setAddress(Address address) {

	this->address = address;
}

void Client::setPacketList(vector<Packet> & packets) {

	this->packets = packets;
}

void Client::setTotalPurchased(unsigned totalPurchased) {

	this->totalPurchased = totalPurchased;
}

// outros metodos

int Client::purchasePacket(vector<Packet> &packets) {

	if (packets.size() == 0) {
		cout << "There are no travel packs registered. " << endl;
		return 1;
	}

	unsigned int input;
	int pack = -1;
	int packExists = 0;
	cout << "Type in the travel pack's identifier that you wish to purchase (type 0 to stop purchase): ";

	while (1) {
		pack = -1;
		input = readInputNumber();

		if (input == 0)
			return 1;

		for (unsigned int i = 0; i < packets.size(); i++) { // check if the pack exists

			if (input == packets.at(i).getId() || input == -packets.at(i).getId()) {
				pack = i;
				break;
			}
		}

		if (packets.at(pack).getId() < 0)
		{
			cout << "Packet unavailable." << endl;
			break;  //checks if identifier is negative
		}
		if (pack == -1) {
			cout << "No such pack exists with that identifier, try again (0 to cancel): ";
			continue;
		}

		for (unsigned int i = 0; i < this->packets.size(); i++) { // check if client already bought the pack

			if (packets.at(pack).getId() == this->packets.at(i).getId() ||
				packets.at(pack).getId() == -this->packets.at(i).getId())
			{
				cout << "The client has already purchased this specific pack, try again (0 to cancel): ";
				packExists = 1;
				break;
			}

		}

		if (packExists == 1) {
			packExists = 0;
			continue;
		}

		if (packets.at(pack).getMaxPersons() - packets.at(pack).getSpotsSold() >= familySize) { // check if it's possible to buy (family restriction)
			this->packets.push_back(packets.at(pack)); // update the client's bought packs
			totalPurchased++;
			packets.at(pack).setSpotsSold(packets.at(pack).getSpotsSold() + familySize); // update the pack's availability
			if (packets.at(pack).getSpotsSold() == packets.at(pack).getMaxPersons())
				packets.at(pack).setId(-packets.at(pack).getId());
			cout << "Pack purchased succesfully. " << endl;
			break;
		}
		else {
			cout << "That pack does not have enough spots for the client's whole family, try again (0 to cancel): ";
			continue;
		}
	}
	return 0;
}

unsigned Client::changeClient() {

	cout << "What do you want to change? (input corresponding number)" << endl;
	cout << "Name (1), VAT number (2), Family size (3), Address (4) (type 0 to cancel at any time)" << endl;

	int option = readInputNumber(0, 4);
	string input;

	cin.clear();
	cin.ignore(200, '\n');

	switch (option) {
	case 0:
		return 1;
	case 1:
		cout << "Current name: " << name << endl;
		cout << "Input new name: ";
		getline(cin, input);
		if (input.length() == 1 && input[0] == '0')
			return 1;
		name = input;
		cout << "Name changed succesfully." << endl;
		break;

	case 2:
		int newVAT;
		cout << "Current VAT number: " << VATnumber << endl;
		cout << "Input new VAT number: ";
		newVAT = readInputNumber();
		if (newVAT == 0)
			return 1;
		VATnumber = newVAT;
		cout << "VAT number changed succesfully." << endl;
		break;

	case 3:
		int newFamilySize;
		if (packets.size() != 0) {
			cout << "Client currently has bought packets, refund them first to change the family's size. " << endl;
			return 1;
		}
		cout << "Current family size: " << familySize << endl;
		cout << "Input new family size: ";
		newFamilySize = readInputNumber();
		if (newFamilySize == 0)
			return 1;
		familySize = newFamilySize;
		cout << "Family size changed succesfully." << endl;
		break;

	case 4:
		cout << "Current address: " << endl << endl;
		cout << address;

		Address newAddress;

		cout << "Input new street name: ";
		getline(cin, input);
		if (input.length() == 1 && input[0] == '0')
			return 1;
		newAddress.setStreet(input);

		cout << "Input new door number: ";
		newAddress.setDoorNumber(readInputNumber());
		if (newAddress.getDoorNumber() == 0)
			return 1;
		cin.clear();
		cin.ignore(200, '\n');

		cout << "Input new floor number (use '-' if not applicable): ";
		getline(cin, input);
		if (input.length() == 1 && input[0] == '0')
			return 1;
		newAddress.setFloor(input);

		cout << "Input new zip code: ";
		getline(cin, input);
		if (input.length() == 1 && input[0] == '0')
			return 1;
		newAddress.setPostalCode(input);

		cout << "Input new locale: ";
		getline(cin, input);
		if (input.length() == 1 && input[0] == '0')
			return 1;
		newAddress.setLocation(input);

		address = newAddress;
		cout << "Address changed succesfully." << endl;
		break;
	}
	cout << "Client changed successfully." << endl;
	return 0;
}

void Client::refundPacket(int chosenPacket, vector<Packet> &packets) {

	if (chosenPacket == -1)
		return;

	for (unsigned int i = 0; i < packets.size(); i++) {

		if (this->packets.at(chosenPacket).getId() == packets.at(i).getId() ||
			this->packets.at(chosenPacket).getId() == -packets.at(i).getId()) {
			packets.at(i).setSpotsSold(packets.at(i).getSpotsSold() - familySize); // update the pack's availability
			packets.at(i).updateIdentifier();
			break;
		}
	}

	totalPurchased--;
	this->packets.erase(this->packets.begin() + chosenPacket);
}

void Client::viewClientPackets(const vector<Packet>& packets) {

	int packNotFound = 0;
	vector<int> unidentifiedPacks;

	if (this->packets.size() != 0)
		cout << "Client " << name << " has bought the following packs:" << endl;
	else
		cout << "Client " << name << " has not bought any packs yet." << endl;

	for (unsigned int i = 0; i < this->packets.size(); i++) {

		for (unsigned int j = 0; j < packets.size(); j++) {

			if (this->packets.at(i).getId() == packets.at(j).getId() ||
				this->packets.at(i).getId() == -packets.at(j).getId()) {
				cout << packets.at(j);
				break;
			}

			if (j == packets.size() - 1)
				packNotFound = 1;
		}

		if (packNotFound == 1) {
			unidentifiedPacks.push_back(this->packets.at(i).getId()); // a pack that is not in the agency's database
			packNotFound = 0;
		}
	}

	if (unidentifiedPacks.size() != 0) {
		cout << "Unidentified packs encountered: ";

		for (unsigned int i = 0; i < unidentifiedPacks.size(); i++) {
			cout << unidentifiedPacks.at(i);
			if (i < unidentifiedPacks.size() - 1)
				cout << ", ";
		}

		cout << endl;
	}
}

ostream& operator<<(ostream& out, const Client & client) {
	out << "===========================" << endl;
	out << "Name: " << client.name << endl;
	out << "VAT number: " << client.VATnumber << endl;
	out << "Number of family members: " << client.familySize << endl;
	out << client.address << endl;
	out << "Identifiers of purchased packs: ";
	for (unsigned int i = 0; i < client.packets.size(); i++) {
		out << client.packets.at(i).getId();
		if (i < client.packets.size() - 1)
			out << "; ";
	}
	out << " - Total purchases: " << client.totalPurchased;
	out << endl;
	out << "===========================" << endl;
	return out;
}
