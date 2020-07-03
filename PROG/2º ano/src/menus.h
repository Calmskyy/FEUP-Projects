#pragma once

#include "Agency.h"

int orderSelection(const vector<Packet> &packets, const string operation); // display all packets, and give option to select 1 for a certain operation

int orderSelection(const vector<Client> &clients, const string operation); // display all clients, and give option to select 1 for a certain operation

void viewAllClientsInfo(const vector<Client> &clients); // display all clients total info

void viewAllPacketsInfo(const vector<Packet> &packets); // display all packets total info

void viewAllPacketsCompactInfo(const vector <Packet> & packets); // display all packets 

unsigned agencyMenu(Agency &agency); // display menu with agency-related functions

unsigned clientMenu(Agency &agency); // display menu with client-related functions

unsigned packetMenu(Agency &agency); // display menu with packet-related functions

unsigned mainMenu(Agency &agency); // display menu that leads into other sub-menus
