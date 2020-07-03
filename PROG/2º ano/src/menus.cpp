#include "Menus.h"

int orderSelection(const vector<Packet>& packets, const string operation) {

	unsigned int inputOrder;
	int chosenPack = -1;
	int currentIdentifier;

	if (packets.size() == 0) {
		cout << "There are no travel packs registered. " << endl;
		return -1;
	}

	cout << "Which travel packet do you want to " << operation << "? (type in the identifier, positive, or 0 to exit): " << endl;
	for (unsigned int i = 0; i < packets.size(); i++) {
		cout << packets.at(i).getId() << " - destination: " << packets.at(i).getMainDestination() << endl; // list all packets
	}

	while (1) {
		inputOrder = readInputNumber();
		if (inputOrder == 0)
			return -1;

		for (unsigned int i = 0; i < packets.size(); i++) {
			currentIdentifier = packets.at(i).getId();

			if (currentIdentifier == inputOrder || -currentIdentifier == inputOrder) { // find the selected packet
				chosenPack = i;
				break;
			}
		}

		if (chosenPack != -1)
			break;
		else {
			cout << "There is no travel packet with that identifier, try again: ";
			cin.clear();
			cin.ignore(200, '\n');
		}
	}
	return chosenPack;
}

int orderSelection(const vector<Client>& clients, const string operation) {

	unsigned int inputOrder;
	int chosenClient = -1;

	cout << "Which client do you want to " << operation << "? (type in the corresponding order number or 0 to exit): " << endl;
	for (unsigned int i = 0; i < clients.size(); i++) {
		cout << clients.at(i).getName() << " - NIF: " << clients.at(i).getVATnumber() << " order:  " << i + 1 << endl; // list all clients
	}

	while (1) {
		inputOrder = readInputNumber();
		if (inputOrder == 0)
			return -1;

		if ((inputOrder - 1) < clients.size())
			chosenClient = (inputOrder - 1); // find the selected client

		if (chosenClient != -1)
			break;
		else {
			cout << "There is no client with that order number, try again: ";
			cin.clear();
			cin.ignore(200, '\n');
		}
	}
	return chosenClient;
}

void viewAllClientsInfo(const vector<Client>& clients) { 

	for (unsigned int i = 0; i < clients.size(); i++) {
		cout << clients.at(i);
	}
}

void viewAllPacketsInfo(const vector<Packet>& packets) { 

	for (unsigned int i = 0; i < packets.size(); i++) {
		cout << packets.at(i);
	}
}

void viewAllPacketsCompactInfo(const vector <Packet> & packets) {

	for (unsigned int i = 0; i < packets.size(); i++) {
		cout << packets.at(i).getId() << ": " << packets.at(i).getMainDestination() << " - ";
		for (unsigned int j = 0; j < packets.at(i).getSecondaryDestinations().size(); j++) {
			if (i == packets.at(i).getSecondaryDestinations().size() - 1) {
				cout << packets.at(i).getSecondaryDestinations().at(j);
				break;
			}
			cout << packets.at(i).getSecondaryDestinations().at(j) << ", ";
		}
		if (packets.at(i).getId() < 0)
			cout << "unavailable";
		else
			cout << "available";
		cout << endl;
	}
}

unsigned agencyMenu(Agency &agency) {

	int option;
	int chosenClient;
	unsigned int N;

	cout << "             || ================== AGENCY =================" << endl;
	cout << "             || (1) Return to main menu" << endl;
	cout << "             || (2) Display the agency's information" << endl;
	cout << "             || (3) View travel packs bought by a specific client" << endl;
	cout << "             || (4) View travel packs bought by all clients" << endl;
	cout << "             || (5) View all purchased packets and their total income" << endl;
	cout << "             || (6) List the most visited locations, in descending order" << endl;
	cout << "             || (7) Recommend an unvisited location for each client, based on the most popular locations" << endl;

	cout << "Type in your option: ";
	option = readInputNumber(1, 7);

	switch (option) {
	case 1:
		return 5; // return to the main menu
	case 2:
		cout << agency << endl;
		break;
	case 3:
		if (agency.getClients().size() != 0) {
			chosenClient = orderSelection(agency.getClients(), "select");
			agency.getClients().at(chosenClient).viewClientPackets(agency.getPackets());
		}
		else
			cout << "There are no remaining clients." << endl;
		break;
	case 4:
		if (agency.getClients().size() != 0) {
			agency.viewAllClientsPackets();
		}
		else
			cout << "There are no remaining clients." << endl;
		break;
	case 5:
		if (agency.getClients().size() != 0) {
			agency.viewTotalPurchasedPackets();
		}
		else
			cout << "There are no registered clients." << endl;
		break;
	case 6:
		if (agency.getPackets().size() != 0){
			cout << "Number of most visited destinations (insert number between 1 and 10, 0 to cancel): " << endl;
			N = readInputNumber(0, 10);
			if (N == 0)
				break;
			agency.viewMostVisitedLocations(PRINT, N);
		}
		else
			cout << "There are no remaining travel packets." << endl;
		return 5;
	case 7:
		if (agency.getPackets().size() != 0) {
			cout << "Suggest pack to each client (insert number of most visited destinations, between 1 and 10, 0 to cancel): " << endl;
			N = readInputNumber(0, 10);
			if (N == 0)
				break;
			agency.viewSuggestedPacksToClients(N);
		}
		else
			cout << "There are no remaining travel packets. " << endl;
		return 5;
	}
	return 2; // return to this menu
}

unsigned clientMenu(Agency &agency) {

	int option;
	int chosenClient;
	int chosenPack;
	vector<Client> agencyClients = agency.getClients();
	vector<Packet> agencyPackets = agency.getPackets();

	cout << "             || ================== CLIENTS =================" << endl;
	cout << "             || (1) Return to main menu" << endl;
	cout << "             || (2) Add a client" << endl;
	cout << "             || (3) Remove a client" << endl;
	cout << "             || (4) Change a client's attributes" << endl;
	cout << "             || (5) View a specific client's info" << endl;
	cout << "             || (6) View ALL clients' info" << endl;
	cout << "             || (7) Purchase a travel pack" << endl;
	cout << "             || (8) Refund a travel pack" << endl;

	cout << "Type in your option: ";
	option = readInputNumber(1, 8);

	switch (option) {
	case 1:
		return 5; // return to main menu
	case 2:
		agency.addClient();
		break;
	case 3:
		if (agency.getClients().size() != 0) {
			chosenClient = orderSelection(agency.getClients(), "remove");
			agency.removeClient(chosenClient);
		}
		else
			cout << "There are no remaining clients." << endl;
		break;
	case 4:
		if (agency.getClients().size() != 0) {
			chosenClient = orderSelection(agency.getClients(), "change");
			if (chosenClient == -1)
				break;
			if (agencyClients.at(chosenClient).changeClient() == 0) {
				agency.setClients(agencyClients);
				agency.setClientsInfoHasChanged(true); // save new data on clients file upon exit
			}
		}
		else
			cout << "There are no remaining clients." << endl;
		break;
	case 5:
		if (agency.getClients().size() != 0) {
			chosenClient = orderSelection(agency.getClients(), "view");
			if (chosenClient == -1)
				break;
			cout << "Selected client info:" << endl;
			cout << agency.getClients().at(chosenClient);
		}
		else
			cout << "There are no remaining clients." << endl;
		break;
	case 6:
		if (agency.getClients().size() != 0) {
			viewAllClientsInfo(agency.getClients());
		}
		else
			cout << "There are no remaining clients." << endl;
		break;
	case 7:
		if (agency.getClients().size() != 0) {
			chosenClient = orderSelection(agency.getClients(), "make the purchase for");
			if (chosenClient == -1)
				break;
			viewAllPacketsCompactInfo(agency.getPackets());
			if (agencyClients.at(chosenClient).purchasePacket(agencyPackets) == 0) {
				agency.setPackets(agencyPackets);
				agency.setClients(agencyClients);
				agency.setClientsInfoHasChanged(true);
				agency.setPacketsInfoHasChanged(true);
			}
		}
		else
			cout << "There are no remaining clients." << endl;
		break;
	case 8:
		if (agency.getClients().size() != 0) {
			chosenClient = orderSelection(agency.getClients(), "refund the purchase for");
			if (chosenClient == -1)
				break;
			if (agency.getClients().at(chosenClient).getPacketList().size() != 0) {
				chosenPack = orderSelection(agency.getClients().at(chosenClient).getPacketList(), "refund");
				if (chosenPack == -1)
					break;
				agencyClients.at(chosenClient).refundPacket(chosenPack, agencyPackets);
				agency.setPackets(agencyPackets);
				agency.setClients(agencyClients);
				agency.setClientsInfoHasChanged(true);
				agency.setPacketsInfoHasChanged(true);
				cout << "Travel packet refunded successfully." << endl;
			}
			else
				cout << "That client doesn't have any purchased travel packets." << endl;
		}
		else
			cout << "There are no remaining clients." << endl;
		break;
	}
	return 3; // return to this menu
}

unsigned packetMenu(Agency &agency) {

	int option;
	int chosenPack;
	string input;
	vector<Packet> agencyPackets = agency.getPackets();

	cout << "             || ================== TRAVEL PACKETS =================" << endl;
	cout << "             || (1) Return to main menu" << endl;
	cout << "             || (2) Add a travel packet" << endl;
	cout << "             || (3) Remove a travel packet" << endl;
	cout << "             || (4) Change a travel packet's attributes" << endl;
	cout << "             || (5) View all travel packets" << endl;
	cout << "             || (6) View all travel packets with a particular destination" << endl;
	cout << "             || (7) View all travel packets between specific dates" << endl;
	cout << "             || (8) View all travel packets between specific dates and with a particular destination" << endl;

	cout << "Type in your option: ";
	option = readInputNumber(1, 8);

	if (option == 6 || option == 8) { // reset stream to be able to use getline()
		cin.clear();
		cin.ignore(200, '\n');
	}

	switch (option) {
	case 1:
		return 5; // return to main menu
	case 2:
		agency.addPacket();
		break;
	case 3:
		if (agency.getPackets().size() != 0) {
			chosenPack = orderSelection(agency.getPackets(), "remove");
			agency.removePacket(chosenPack);
		}
		else
			cout << "There are no remaining travel packets." << endl;
		break;
	case 4:
		if (agency.getPackets().size() != 0) {
			chosenPack = orderSelection(agency.getPackets(), "change");
			if (chosenPack == -1)
				break;
			if (agencyPackets.at(chosenPack).changePacket() == 0) {
				agency.setPackets(agencyPackets);
				agency.setPacketsInfoHasChanged(true);
				agency.sortPackets();
			}
		}
		else
			cout << "There are no remaining travel packets." << endl;
		break;
	case 5:
		if (agency.getPackets().size() != 0) {
			viewAllPacketsInfo(agency.getPackets());
		}
		else
			cout << "There are no remaining travel packets." << endl;
	case 6:
		if (agency.getPackets().size() != 0) {
			cout << "Type in the destination you want to search for: " << endl;
			getline(cin, input);
			agency.viewSameDestinationPackets(input, PRINT);
		}
		else
			cout << "There are no remaining travel packets." << endl;
		break;
	case 7:
		if (agency.getPackets().size() != 0) {
			agency.viewBetweenDatePackets(agency.getPackets());
		}
		else
			cout << "There are no remaining travel packets." << endl;
		break;
	case 8:
		if (agency.getPackets().size() != 0) {
			cout << "Type in the destination you want to search for: " << endl;
			getline(cin, input);
			agency.viewBetweenDateSameDestinationPackets(input);
		}
		else
			cout << "There are no remaining travel packets." << endl;
		break;
	}
	return 4; // return to this menu
}

unsigned mainMenu(Agency &agency) {

	int option;

	cout << endl;
	cout << "             || ================== MENU =================" << endl;
	cout << "             || Input the corresponding number to navigate through the menu." << endl;
	cout << "             || (1) Exit" << endl;
	cout << "             || (2) Agency/statistics related tasks" << endl;
	cout << "             || (3) Client related tasks" << endl;
	cout << "             || (4) Packet related tasks" << endl;

	cout << "Type in your option: ";
	option = readInputNumber(1, 4);

	return option; // enter a certain sub-menu
}

