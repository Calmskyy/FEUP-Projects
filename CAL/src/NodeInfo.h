#pragma once

#include <string>

class NodeInfo {
	double x, y, lat, lon;
	int id;
	std::string tag;

public:
	NodeInfo(double x, double y, int id);
	double getX() const;
	double getY() const;
	double getLat() const;
	double getLon() const;
	int getID() const;
	std::string getTag() const;
	void setTag(std::string tag);
	void setLat(double lat);
	void setLon(double lon);
	bool operator == (const NodeInfo &info) const;
};

