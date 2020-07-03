#include "Vehicle.h"

Vehicle::Vehicle(string tag){

	this->tag = tag;
}

string Vehicle::getTag()
{
	return tag;
}

vector<Vertex*> Vehicle::getPickUpLocs()
{
	return pickUpLocs;
}

vector<Vertex*> Vehicle::getDeliveryLocs()
{
	return deliveryLocs;
}

void Vehicle::setTag(string tag)
{
	this->tag = tag;
}

void Vehicle::setPickUpLocs(vector<Vertex*> pickUpLocs)
{
	this->pickUpLocs = pickUpLocs;
}

void Vehicle::setDeliveryLocs(vector<Vertex*> deliveryLocs)
{
	this->deliveryLocs = deliveryLocs;
}
