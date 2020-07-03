#pragma once

#include <string>
#include <fstream>
#include <iomanip>

#include "Agency.h"

void saveFiles(const Agency &agency);

void saveAgency(const Agency &agency);

void saveClients(const vector <Client> &clients, const string clientsFileName);

void savePackets(const vector<Packet> &packets, const string packetsFileName);

