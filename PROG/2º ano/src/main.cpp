#include <iostream>
#include <string>
#include <map>

#include "Agency.h"
#include "Menus.h"
#include "Saves.h"

int main() {
	cout << "TOURISM AGENCY PROGRAM" << endl;
	cout << "=======================================" << endl; cout << endl;

	Agency agency(AGENCY_FILE_NAME);   // create the agency

	cout << "Loading finished!\n";

	agency.sortPackets(); // add the packs' attributes to each client's pack vector

	map<unsigned, unsigned(*)(Agency&)> menuMap = { // map with function pointers, navigates through menus based on the menus' return values
	{2, agencyMenu},
	{3, clientMenu},
	{4, packetMenu},
	{5, mainMenu}
	};

	unsigned returnValue = 5; // initialize with the main menu

	while (returnValue > 1) {
		returnValue = menuMap.at(returnValue)(agency); // keep track of what the previous menu was
	}

	saveFiles(agency); // save files at the end if necessary

	system("PAUSE");
	return 0;
}
