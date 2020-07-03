#include "NodeInfo.h"

NodeInfo::NodeInfo(double x, double y, int id) {
	this->x = x;
	this->y = y;
	this->id = id;
	this->tag = "";
}

double NodeInfo::getX() const {
	return x;
}

double NodeInfo::getY() const {
	return y;
}

double NodeInfo::getLat() const {
	return lat;
}

double NodeInfo::getLon() const {
	return lon;
}

int NodeInfo::getID() const {
	return id;
}

std::string NodeInfo::getTag() const {
	return tag;
}

void NodeInfo::setTag(std::string tag) {
	this->tag = tag;
}

void NodeInfo::setLat(double lat) {
	this->lat = lat;
}

void NodeInfo::setLon(double lon) {
	this->lon = lon;
}

bool NodeInfo::operator ==(const NodeInfo &info) const {
	return (x == info.x && y == info.y && id == info.id && tag == info.tag);
}
