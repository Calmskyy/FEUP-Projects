#include "Saves.h"

void saveFiles(const Agency &agency) { // save new data on files

	cout << "Checking if saving is necessary...\n";

	if (agency.getAgencyInfoHasChanged() == true) {
		cout << "Agency information has changed! Saving new information...\n";
		saveAgency(agency);
	}
	if (agency.getClientsInfoHasChanged() == true) {
		cout << "Clients information has changed! Saving new information...\n";
		saveClients(agency.getClients(), agency.getClientsFileName());
	}
	if (agency.getPacketsInfoHasChanged() == true) {
		cout << "Packets information has changed! Saving new information...\n";
		savePackets(agency.getPackets(), agency.getPacketsFileName());
	}

	cout << "Finished saving!\n";
}

void saveAgency(const Agency &agency) { // save new data on the Agency file

	ofstream agencyFile;

	agencyFile.open(agency.getAgencyFileName());

	if (agencyFile.fail())
	{
		cerr << "File not found!\n";
		cerr << "Could not save agency details.\n";
		return;
	}

	cout << "Saving agency details...\n";
	cout << "=======================================\n\n";

	agencyFile << agency.getName() << endl;

	agencyFile << agency.getVATnumber() << endl;

	agencyFile << agency.getURL() << endl;

	agencyFile << agency.getAddress().getStreet() << " / ";
	agencyFile << agency.getAddress().getDoorNumber() << " / ";
	agencyFile << agency.getAddress().getFloor() << " / ";
	agencyFile << agency.getAddress().getPostalCode() << " / ";
	agencyFile << agency.getAddress().getLocation() << endl;

	agencyFile << agency.getClientsFileName() << endl;

	agencyFile << agency.getPacketsFileName() << endl;

	agencyFile.close();
}

void saveClients(const vector<Client>& clients, const string clientsFileName) { // save new data on the Clients file

	ofstream clientFile;

	clientFile.open(clientsFileName);

	if (clientFile.fail())
	{
		cerr << "File not found!\n";
		cerr << "Could not save client details.\n";
		return;
	}

	cout << "Saving client details...\n";
	cout << "=======================================\n\n";

	for (unsigned int i = 0; i < clients.size(); i++) {

		clientFile << clients.at(i).getName() << endl;

		clientFile << clients.at(i).getVATnumber() << endl;

		clientFile << clients.at(i).getFamilySize() << endl;

		clientFile << clients.at(i).getAddress().getStreet() << " / ";
		clientFile << clients.at(i).getAddress().getDoorNumber() << " / ";
		clientFile << clients.at(i).getAddress().getFloor() << " / ";
		clientFile << clients.at(i).getAddress().getPostalCode() << " / ";
		clientFile << clients.at(i).getAddress().getLocation() << endl;

		for (unsigned int j = 0; j < clients.at(i).getPacketList().size(); j++) {

			clientFile << clients.at(i).getPacketList().at(j).getId();
			if (j < clients.at(i).getPacketList().size() - 1)
				clientFile << "; ";
		}

		clientFile << endl;

		if (i < clients.size() - 1)
			clientFile << "::::::::::" << endl;
	}
	clientFile.close();
}

void savePackets(const vector<Packet>& packets, const string packetsFileName) { // save new data on the Packets file

	ofstream travelPackFile;

	travelPackFile.open(packetsFileName);

	if (travelPackFile.fail())
	{
		cerr << "File not found!\n";
		cerr << "Could not save travel pack details.\n";
		return;
	}

	cout << "Saving travel pack details...\n";
	cout << "=======================================\n\n";

	int lastPackWrite = 0;

	for (unsigned int i = 0; i < packets.size(); i++) {

		if (lastPackWrite == 0) {
			travelPackFile << packets.at(packets.size() - 1).getId() << endl;
			lastPackWrite = 1;
		}

		travelPackFile << packets.at(i).getId() << endl;

		if (packets.at(i).getSecondaryDestinations().size() != 0) {
			travelPackFile << packets.at(i).getMainDestination() << " - ";
			for (unsigned int j = 0; j < packets.at(i).getSecondaryDestinations().size(); j++) {
				if (j == packets.at(i).getSecondaryDestinations().size() - 1) {
					travelPackFile<< packets.at(i).getSecondaryDestinations().at(j);
					break;
				}
				travelPackFile << packets.at(i).getSecondaryDestinations().at(j) << ", ";
			}
			travelPackFile << endl;
		}
		else
			travelPackFile << packets.at(i).getMainDestination() << endl;

		travelPackFile << packets.at(i).getBeginDate().getYear() << "/" << packets.at(i).getBeginDate().getMonth() << "/";
		travelPackFile << packets.at(i).getBeginDate().getDay() << endl << packets.at(i).getEndDate().getYear() << "/";
		travelPackFile << packets.at(i).getEndDate().getMonth() << "/" << packets.at(i).getEndDate().getDay() << endl;

		travelPackFile << packets.at(i).getPricePerPerson() << endl;

		travelPackFile << packets.at(i).getMaxPersons() << endl;

		travelPackFile << packets.at(i).getSpotsSold() << endl;
		if (i < packets.size() - 1)
			travelPackFile << "::::::::::" << endl;
	}
	travelPackFile.close();
}
