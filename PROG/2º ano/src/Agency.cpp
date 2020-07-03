#include "Agency.h"

Agency::Agency(string fileName) {

	ifstream agencyFile;
	agencyFile.open(fileName);

	if (agencyFile.fail()) {
		cerr << "Agency file not found!\n";
		exit(1);
	}

	agencyFileName = fileName;
	string s;
	int count = 0;

	while (getline(agencyFile, s)) {
		switch (count) {
		case 0:
			name = s;
			break;
		case 1:
			VATnumber = stoul(s, nullptr, 0);
			break;
		case 2:
			URL = s;
			break;
		case 3:
			address = Address(s);
			break;
		case 4:
			clients = loadClients(s);
			clientsFileName = s;
			break;
		case 5:
			packets = loadPackets(s);
			packetsFileName = s;
			break;
		}
		if (count == 5)
			break;
		count++;
	}

	clientsInfoHasChanged = false;
	packetsInfoHasChanged = false;
	agencyInfoHasChanged = false;
	maxClientsId = MAX_CLIENTS;
	maxPacketsId = MAX_PACKETS;
	agencyFile.close();
}

// metodos GET

string Agency::getName() const {

	return name;
}

unsigned Agency::getVATnumber() const {

	return VATnumber;
}

Address Agency::getAddress() const {

	return address;
}

string Agency::getURL() const {

	return URL;
}

vector<Client> Agency::getClients() const {

	return clients;
}

vector<Packet> Agency::getPackets() const {

	return packets;
}

string Agency::getAgencyFileName() const
{
	return agencyFileName;
}

string Agency::getClientsFileName() const
{
	return clientsFileName;
}

string Agency::getPacketsFileName() const
{
	return packetsFileName;
}

bool Agency::getClientsInfoHasChanged() const {

	return clientsInfoHasChanged;
}

bool Agency::getPacketsInfoHasChanged() const {

	return packetsInfoHasChanged;
}

bool Agency::getAgencyInfoHasChanged() const {

	return agencyInfoHasChanged;
}

unsigned Agency::getMaxClientsId() const {

	return maxClientsId;
}

unsigned Agency::getMaxPacketsId() const {

	return maxPacketsId;
}

// SET Methods

void Agency::setName(string name) {

	this->name = name;
}

void Agency::setVATnumber(unsigned VATnumber) {

	this->VATnumber = VATnumber;
}

void Agency::setAddress(Address address) {

	this->address = address;
}

void Agency::setURL(string URL) {

	this->URL = URL;
}

void Agency::setClients(vector<Client> & clients) {

	this->clients = clients;
}

void Agency::setPackets(vector<Packet> & packets) {

	this->packets = packets;
}

void Agency::setClientsInfoHasChanged(bool clientsInfoHasChanged) {

	this->clientsInfoHasChanged = clientsInfoHasChanged;
}

void Agency::setPacketsInfoHasChanged(bool packetsInfoHasChanged) {

	this->packetsInfoHasChanged = packetsInfoHasChanged;
}

void Agency::setAgencyInfoHasChanged(bool agencyInfoHasChanged) {

	this->agencyInfoHasChanged = agencyInfoHasChanged;
}

void Agency::sortPackets() {

	int tempIdentifier;

	vector<Packet> clientPackets;

	for (unsigned int i = 0; i < clients.size(); i++) { // copy packets info to the clients
		clientPackets = clients.at(i).getPacketList();

		for (unsigned int j = 0; j < clients.at(i).getPacketList().size(); j++) {
			tempIdentifier = clients.at(i).getPacketList().at(j).getId();
			if (tempIdentifier < 0)
				tempIdentifier = -tempIdentifier;
			if ((unsigned int)tempIdentifier <= packets.size())
				clientPackets.at(j).copyPacket(packets.at(tempIdentifier - 1));
		}
		clients.at(i).setPacketList(clientPackets);
		clients.at(i).setTotalPurchased(clients.at(i).getPacketList().size());
	}
}

vector<Client> Agency::loadClients(string fileName) {

	ifstream clientFile;

	clientFile.open(fileName);

	if (clientFile.fail())
	{
		cerr << "Client file not found!\n";
		exit(1);
	}

	string s;
	int count = 0;
	int packetCount = 0;
	Client client;
	Packet packet;
	char delim = ';';
	size_t pos = 0;
	size_t temp_pos = 0;
	string data;

	vector<Client> clients;
	vector<Packet> packets;

	while (getline(clientFile, s)) {
		switch (count) {
		case -1:
			break;
		case 0:
			client.setName(s);
			break;
		case 1:
			client.setVATnumber(stoi(s, nullptr, 0));
			break;
		case 2:
			client.setFamilySize((unsigned short)stoi(s, nullptr, 0));
			break;
		case 3:
			client.setAddress(Address(s));
			break;
		case 4:
			while (1) {
				pos = s.find(delim, temp_pos);
				if (pos == npos) {
					data = s.substr(temp_pos, s.length() - pos);
					if (data != "") {
						packet.setId(stoi(data, nullptr, 0));
						packets.push_back(packet); // gets every packet the client bought
						packetCount++;
					}
					break;
				}
				data = s.substr(temp_pos, pos);
				temp_pos = pos + 2;
				packet.setId(stoi(data, nullptr, 0));
				packets.push_back(packet);
				packetCount++;
			}
			client.setTotalPurchased(packetCount);
			client.setPacketList(packets);
			clients.push_back(client);
			count = -2;
			pos = 0;
			temp_pos = 0;
			packets.clear();
			break;
		default:
			break;
		}
		count++;
	}
	clientFile.close();
	return clients;
}

vector<Packet> Agency::loadPackets(string fileName) {

	ifstream packetFile;

	packetFile.open(fileName);

	if (packetFile.fail())
	{
		cerr << "Packets file not found!\n";
		exit(1);
	}

	string s;
	int count = -3;
	Packet packet;
	char delim = '-';
	size_t pos = 0;
	size_t temp_pos = 0;
	string data;

	vector<Packet> packets;

	while (getline(packetFile, s)) {
		if (count == -3) {
			count = 0;
			continue;
		}
		if (count == -1) {
			count++;
			continue;
		}
		if (count == 0)
			packet.setId(stoi(s, nullptr, 0));

		if (count == 1) {
			pos = s.find(delim, temp_pos);
			if (pos == npos) {
				packet.setMainDestination(s);
				count++;
				continue;
			}
			data = s.substr(temp_pos, pos - 1);
			packet.setMainDestination(data);
			data = s.substr(pos + 2, s.length() - pos - 2);
			packet.readAndSetSecondaryDestinations(data); // loads the destinations vector based on the text string
		}
		if (count == 2)
			packet.setBeginDate(Date(s));
		if (count == 3)
			packet.setEndDate(Date(s));
		if (count == 4)
			packet.setPricePerPerson(stoul(s, nullptr, 0));
		if (count == 5)
			packet.setMaxPersons(stoul(s, nullptr, 0));
		if (count == 6) {
			packet.setSpotsSold(stoul(s, nullptr, 0));
			if (packet.getSpotsSold() < packet.getMaxPersons())
				if (packet.getId() < 0)
					packet.setUnavailable(true);
			packets.push_back(packet);
			packet.readAndSetSecondaryDestinations("");
			count = -1;
			continue;
		}
		count++;
	}
	packetFile.close();
	return packets;
}

void Agency::removeClient(int chosenClient) {

	if (chosenClient == -1)
		return;

	int updatedPacks = 0;

	for (unsigned int i = 0; i < clients.at(chosenClient).getPacketList().size(); i++) { // check all the packs the client has bought

		for (unsigned int j = 0; j < packets.size(); j++) {

			if (clients.at(chosenClient).getPacketList().at(i).getId() == packets.at(j).getId() ||
				clients.at(chosenClient).getPacketList().at(i).getId() == -packets.at(j).getId()) {
				packets.at(j).setSpotsSold(packets.at(j).getSpotsSold() - clients.at(chosenClient).getFamilySize()); // update the availability of the packs
				packets.at(j).updateIdentifier();
				updatedPacks++;
				break;
			}
		}
	}

	clients.erase(clients.begin() + chosenClient);
	cout << "Client removed successfully." << endl;
	if (updatedPacks > 0)
		packetsInfoHasChanged = true;
	clientsInfoHasChanged = true;
	agencyInfoHasChanged = true;
}

void Agency::addClient() {

	if (clients.size() == maxClientsId) {
		cout << "Reached maximum number of clients (" << maxClientsId << "), can't add more." << endl;
		return;
	}

	Client client;
	string input;

	cin.clear();
	cin.ignore(200, '\n');

	cout << "Please input the following client attributes (type 0 at any time to cancel):" << endl << endl;

	cout << "Input a name: ";
	getline(cin, input);
	if (input.length() == 1 && input[0] == '0')
		return;
	client.setName(input);

	cout << "Input new VAT: ";
	client.setVATnumber(readInputNumber());
	if (client.getVATnumber() == 0)
		return;

	cout << "Input new family size: ";
	client.setFamilySize(readInputNumber());
	if (client.getFamilySize() == 0)
		return;

	cin.clear();
	cin.ignore(200, '\n');

	Address address;

	cout << "Address - Input new street name: ";
	getline(cin, input);
	if (input.length() == 1 && input[0] == '0')
		return;
	address.setStreet(input);

	cout << "Address - Input new door number: ";
	address.setDoorNumber(readInputNumber());
	if (address.getDoorNumber() == 0)
		return;
	cin.clear();
	cin.ignore(200, '\n');

	cout << "Address - Input new floor number (use '-' if not applicable): ";
	getline(cin, input);
	if (input.length() == 1 && input[0] == '0')
		return;
	address.setFloor(input);

	cout << "Address - Input new zip code: ";
	getline(cin, input);
	if (input.length() == 1 && input[0] == '0')
		return;
	address.setPostalCode(input);

	cout << "Address - Input new locale: ";
	getline(cin, input);
	if (input.length() == 1 && input[0] == '0')
		return;
	address.setLocation(input);

	client.setAddress(address);

	client.setTotalPurchased(0);

	cout << "Client added successfully." << endl;
	clients.push_back(client);
	clientsInfoHasChanged = true;
	agencyInfoHasChanged = true;
}

void Agency::removePacket(int chosenPacket) {

	if (chosenPacket == -1)
		return;
	else if (packets.at(chosenPacket).getId() > 0) {
		packets.at(chosenPacket).setId(-packets.at(chosenPacket).getId());
		packets.at(chosenPacket).setUnavailable(true);
	}

	cout << "Travel pack removed successfully." << endl;
	packetsInfoHasChanged = true;
	agencyInfoHasChanged = true;
}

void Agency::addPacket() {

	if (packets.size() == maxPacketsId) {
		cout << "Reached maximum number of packets (" << maxPacketsId << "), can't add more." << endl;
		return;
	}

	Packet packet;
	string input;
	vector<string> secDest;

	cin.clear();
	cin.ignore(200, '\n');

	cout << "Please input the following travel packet attributes (type 0 at any time to cancel):" << endl << endl;

	cout << "Input the main destination: " << endl;
	getline(cin, input);
	if (input.length() == 1 && input[0] == '0')
		return;
	packet.setMainDestination(input);


	cout << "Input the secondary destinations(type 1 if there are none): " << endl << "Each destination must be separated by a comma and a space(x, y) :" << endl;
	getline(cin, input);

	if (input.length() == 1 && input[0] == '0')
		return;
	else if (input.length() == 1 && input[0] == '1')
		packet.readAndSetSecondaryDestinations("");
	else
		packet.readAndSetSecondaryDestinations(input);



	bool dateCheck;

	Date begin, end;

	while (1) {

		cout << "Input the start date - year: " << endl;
		begin.setYear(readInputNumber());
		if (begin.getYear() == 0)
			return;
		cout << "Input the start date - month: " << endl;
		begin.setMonth(readInputNumber());
		if (begin.getMonth() == 0)
			return;
		cout << "Input the start date - day: " << endl;
		begin.setDay(readInputNumber());
		if (begin.getDay() == 0)
			return;

		if (begin.checkValidYear() == false) {
			cout << "Year is invalid! Please input a year between 2019 and 2030." << endl;
			continue;
		}
		if (begin.checkValidMonth() == false) {
			cout << "Month is invalid! Please input a month between 1 and 12." << endl;
			continue;
		}
		if (begin.checkValidDay() == false) {
			cout << "Day is invalid! Please input a valid day (depends on the chosen month)." << endl;
			continue;
		}

		packet.setBeginDate(begin);

		cout << "Input the end date - year: " << endl;
		end.setYear(readInputNumber());
		if (end.getYear() == 0)
			return;
		cout << "Input the end date - month: " << endl;
		end.setMonth(readInputNumber());
		if (end.getMonth() == 0)
			return;
		cout << "Input the end date - day: " << endl;
		end.setDay(readInputNumber());
		if (end.getDay() == 0)
			return;

		if (end.checkValidYear() == false) {
			cout << "Year is invalid! Please input a year between 2019 and 2030." << endl;
			continue;
		}
		if (end.checkValidMonth() == false) {
			cout << "Month is invalid! Please input a month between 1 and 12." << endl;
			continue;
		}
		if (end.checkValidDay() == false) {
			cout << "Day is invalid! Please input a valid day (depends on the chosen month)." << endl;
			continue;
		}

		packet.setEndDate(end);

		dateCheck = packet.getBeginDate().checkOrderDates(packet.getEndDate());
		if (dateCheck == true)
			break;
		else {
			cout << "End date comes after the start date! Put them in correct order." << endl;
		}
	}

	cout << "Input the price: " << endl;
	packet.setPricePerPerson(readDoubleInputNumber(0, 2000));
	if (packet.getPricePerPerson() == 0)
		return;

	cout << "Input the max amount of people: " << endl;
	packet.setMaxPersons(readInputNumber());
	if (packet.getMaxPersons() == 0)
		return;

	packet.setSpotsSold(0);

	packet.setId(packets.size() + 1);

	cout << "Travel pack added successfully." << endl;
	packets.push_back(packet);
	packetsInfoHasChanged = true;
	agencyInfoHasChanged = true;
}

vector<Packet> Agency::viewSameDestinationPackets(const string destination, int printOption) {

	int count = 0;
	vector<Packet> returnPackets;
	string packDestination;
	vector<string> packSecondaryDestinations;
	string secDestination;

	for (unsigned int i = 0; i < packets.size(); i++) {
		packDestination = packets.at(i).getMainDestination();

		if (_stricmp(&destination[0], &packDestination[0]) == 0) { // case-insensitive comparison
			if (printOption == PRINT) // mode to print the packs on the screen
				cout << packets.at(i);
			returnPackets.push_back(packets.at(i));
			count++;
		}
	}

	for (unsigned int i = 0; i < packets.size(); i++) {
		packSecondaryDestinations = packets.at(i).getSecondaryDestinations();
		if (packSecondaryDestinations.empty())
			continue;
		for (unsigned int j = 0; j < packSecondaryDestinations.size(); j++) {
			secDestination = packSecondaryDestinations.at(j);
			if (_stricmp(&destination[0], &secDestination[0]) == 0) { // case-insensitive comparison
				if (printOption == PRINT) // mode to print the packs on the screen
					cout << packets.at(i);
				returnPackets.push_back(packets.at(i));
				count++;
			}
		}
	}

	if (count == 0)
		cout << "There are no travel packs with that destination." << endl;

	return returnPackets; // this pack is used as a filter for viewing packs with same destination and between specific dates
}

void Agency::viewBetweenDatePackets(const vector<Packet> &packets) {

	int count = 0;
	Date firstDate;
	Date secondDate;

	bool dateCheck;

	while (1) {

		cout << "Input the first date - year: " << endl;
		firstDate.setYear(readInputNumber());

		cout << "Input the first date - month: " << endl;
		firstDate.setMonth(readInputNumber());

		cout << "Input the first date - day: " << endl;
		firstDate.setDay(readInputNumber());

		if (firstDate.checkValidYear() == false) {
			cout << "Year is invalid! Please input a year between 2019 and 2030." << endl;
			continue;
		}
		if (firstDate.checkValidMonth() == false) {
			cout << "Month is invalid! Please input a month between 1 and 12." << endl;
			continue;
		}
		if (firstDate.checkValidDay() == false) {
			cout << "Day is invalid! Please input a valid day (depends on the chosen month)." << endl;
			continue;
		}

		cout << "Input the second date - year: " << endl;
		secondDate.setYear(readInputNumber());

		cout << "Input the second date - month: " << endl;
		secondDate.setMonth(readInputNumber());

		cout << "Input the second date - day: " << endl;
		secondDate.setDay(readInputNumber());

		if (secondDate.checkValidYear() == false) {
			cout << "Year is invalid! Please input a year between 2019 and 2030." << endl;
			continue;
		}
		if (secondDate.checkValidMonth() == false) {
			cout << "Month is invalid! Please input a month between 1 and 12." << endl;
			continue;
		}
		if (secondDate.checkValidDay() == false) {
			cout << "Day is invalid! Please input a valid day (depends on the chosen month)." << endl;
			continue;
		}

		dateCheck = firstDate.checkOrderDates(secondDate);
		if (dateCheck == true)
			break;
		else {
			cout << "Second date should come after the first date! Put them in the correct order." << endl;
		}
	}

	for (unsigned int i = 0; i < packets.size(); i++) {

		if (firstDate.checkOrderDates(packets.at(i).getBeginDate()) == true &&
			packets.at(i).getEndDate().checkOrderDates(secondDate) == true) { // check if the pack is between the specific date
			cout << packets.at(i);
			count++;
		}
	}

	if (count == 0)
		cout << "There are no travel packs in between those dates. " << endl;
}

void Agency::viewBetweenDateSameDestinationPackets(const string destination) {

	vector<Packet> sameDestinationPackets = viewSameDestinationPackets(destination, NO_PRINT);
	// don't print the packs on the screen

	if (sameDestinationPackets.size() == 0)
		return;
	else
		viewBetweenDatePackets(sameDestinationPackets);
}

void Agency::viewAllClientsPackets() {

	for (unsigned int i = 0; i < clients.size(); i++) {

		clients.at(i).viewClientPackets(packets);
	}
}

void Agency::viewTotalPurchasedPackets() {

	unsigned int purchasedPacks = 0;
	unsigned int peopleAmount = 0;
	unsigned int unidentifiedPacks = 0;
	double moneyGained = 0;

	int tempIdentifier;

	for (unsigned int i = 0; i < clients.size(); i++) {

		for (unsigned int j = 0; j < clients.at(i).getPacketList().size(); j++) {

			tempIdentifier = clients.at(i).getPacketList().at(j).getId();
			if (tempIdentifier < 0)
				tempIdentifier = -tempIdentifier;
			if ((unsigned int)tempIdentifier > packets.size()) // check for packs that aren't on the database
				unidentifiedPacks++;
			else {
				purchasedPacks++;
				peopleAmount += clients.at(i).getFamilySize(); // add to the amount of people that have a pack deal
				moneyGained += clients.at(i).getFamilySize() * clients.at(i).getPacketList().at(j).getPricePerPerson(); // add the money generated from the pack purchase
			}
		}
	}

	if (unidentifiedPacks > 0) {
		if (unidentifiedPacks == 1)
			cout << "Found " << unidentifiedPacks << " pack bought that is not on the database. Final results won't count this one." << endl;
		else
			cout << "Found " << unidentifiedPacks << " packs bought that are not on the database. Final results won't count these." << endl;
	}

	// different scenarios to print depending on how many packs/people found
	if (peopleAmount == 0 || purchasedPacks == 0) {
		cout << "No packs have been purchased yet." << endl;
		return;
	}
	if (peopleAmount == 1 && purchasedPacks == 1)
		cout << purchasedPacks << " pack for " << peopleAmount << " person has been purchased." << endl;
	else if (peopleAmount == 1)
		cout << purchasedPacks << " packs for " << peopleAmount << " person have been purchased." << endl;
	else if (purchasedPacks == 1)
		cout << purchasedPacks << " pack for a total of " << peopleAmount << " people has been purchased." << endl;
	else
		cout << purchasedPacks << " packs for a total of " << peopleAmount << " people have been purchased." << endl;
	cout << fixed << setprecision(2);
	cout << "Total income: " << moneyGained << endl;
}

vector<string> Agency::viewMostVisitedLocations(int printOption, unsigned &N) {
	vector<string>visitedLocations;
	string location;
	bool foundDestination = false;
	multimap <unsigned int, string> numberOfVisits;
	vector<Packet> sameLocationsPackets;
	unsigned int visits = 0;
	unsigned int counter = 0;
	vector<string> returnLocations;


	for (unsigned int j = 0; j < packets.size(); j++)   //creation of a vector with all locations without repetition
	{
		location = packets.at(j).getMainDestination();

		vector<string>::iterator it;
		it = find(visitedLocations.begin(), visitedLocations.end(), location);
		if (it != visitedLocations.end())
			foundDestination = true;
		else if (foundDestination != true)
		{
			visitedLocations.push_back(location);
		}

		foundDestination = false;
		if (packets.at(j).getSecondaryDestinations().size() != 0) {
			for (unsigned int k = 0; k < packets.at(j).getSecondaryDestinations().size(); k++)
			{
				location = packets.at(j).getSecondaryDestinations().at(k);

				vector<string>::iterator it;
				it = find(visitedLocations.begin(), visitedLocations.end(), location);
				if (it != visitedLocations.end())
					foundDestination = true;
				else if (foundDestination != true)
				{
					visitedLocations.push_back(location);
				}

				foundDestination = false;
			}

		}
	}

	for (unsigned int i = 0; i < visitedLocations.size(); i++)  //filling the multimap with number of times visited as key and location as value
	{
		sameLocationsPackets = viewSameDestinationPackets(visitedLocations.at(i), NO_PRINT);

		for (unsigned int j = 0; j < sameLocationsPackets.size(); j++)
		{
			visits = visits + sameLocationsPackets.at(j).getSpotsSold();
		}

		numberOfVisits.insert({ visits, visitedLocations.at(i) });
		visits = 0;
	}

	if (printOption == PRINT) // mode to print multimap on the screen
	{
		cout << "The " << N << " most visited locations are: " << endl;

		multimap <int, string> ::reverse_iterator ritr;

		for (auto ritr = numberOfVisits.rbegin(); ritr != numberOfVisits.rend(); ritr++)
		{
			if (counter < N)
				cout << counter + 1 << " = " << ritr->second << endl;
			counter++;
		}

	}

	counter = 0;          //to fill the vector returnLocations with N most visited locations to pass to viewSuggestedPacksToClients
	for (auto ritr = numberOfVisits.rbegin(); ritr != numberOfVisits.rend(); ritr++)
	{
		if (counter < N)
			returnLocations.push_back(ritr->second);
		counter++;
	}

	cout << endl;

	return returnLocations;
}

void Agency::viewSuggestedPacksToClients(unsigned &N) {
	vector<string> mostVisitedLocations;
	vector<Packet> mostVisitedPacket;
	vector<int> idOfMostVisitedPackets;
	vector<int> clientsBoughtPacks;
	string location;
	int suggestedFlag = 0;

	mostVisitedLocations = viewMostVisitedLocations(NO_PRINT, N);   //vector with N most visited locations

	for (unsigned int i = 0; i < mostVisitedLocations.size(); i++) {  //vector with id of most visited packets(excluding the negatives)
		location = mostVisitedLocations.at(i);
		mostVisitedPacket = viewSameDestinationPackets(location, NO_PRINT);  //packets of that location

		for (unsigned int j = 0; j < mostVisitedPacket.size(); j++) {
			if (mostVisitedPacket.at(j).getId() > 0)
				idOfMostVisitedPackets.push_back(mostVisitedPacket.at(j).getId());
		}
	}

	if (clients.size() != 0) {
		for (unsigned int i = 0; i < clients.size(); i++) {
			for (unsigned int j = 0; j < clients.at(i).getPacketList().size(); j++) {
				clientsBoughtPacks.push_back(clients.at(i).getPacketList().at(j).getId());  //fill vector with id of packs bought by client i
			}

			for (unsigned int k = 0; k < idOfMostVisitedPackets.size(); k++) {
				suggestedFlag = 1;
				vector<int>::iterator it;
				it = find(clientsBoughtPacks.begin(), clientsBoughtPacks.end(), idOfMostVisitedPackets.at(k));

				if (k == (idOfMostVisitedPackets.size() - 1) && it != clientsBoughtPacks.end())
					cout << "No available suggestions to " << clients.at(i).getName() << "." << endl;

				if (it != clientsBoughtPacks.end())
					continue;
				else
				{
					cout << "Packet " << idOfMostVisitedPackets.at(k) << " suggested to " << clients.at(i).getName() << "." << endl;
					break;
				}
			}
			clientsBoughtPacks.clear();
		}
	}
	else {
		cout << "No clients remaining." << endl;
		return;
	}

	if (suggestedFlag == 0)
		cout << "No suggestions available (packets chosen from the top are all unavailable)." << endl;
}

ostream& operator<<(ostream& out, const Agency & agency) {

	out << "===========================" << endl;
	out << "Agency name: " << agency.name << endl;
	out << "VAT number: " << agency.VATnumber << endl;
	out << agency.address << endl;
	out << "Website URL: " << agency.URL << endl;
	out << "Number of registered clients: " << agency.clients.size() << endl;
	out << "Number of registered packets: " << agency.packets.size() << endl;
	out << "===========================" << endl;
	return out;
}
