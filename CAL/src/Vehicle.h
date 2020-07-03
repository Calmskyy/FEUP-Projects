#pragma once

#include <string>
#include <vector>
#include "NodeInfo.h"
#include "Graph.h"

using std::string;
using std::vector;

class Vehicle{
	string tag;
	vector<Vertex*> pickUpLocs;
	vector<Vertex*> deliveryLocs;
public:
	Vehicle(string tag);
	string getTag();
	vector<Vertex*> getPickUpLocs();
	vector<Vertex*> getDeliveryLocs();
	void setTag(string tag);
	void setPickUpLocs(vector<Vertex*> pickUpLocs);
	void setDeliveryLocs(vector<Vertex*> deliveryLocs);
};

