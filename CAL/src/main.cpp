#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include "Graph.h"
#include "NodeInfo.h"
#include "Utilities.h"
#include "Vehicle.h"
using namespace std;

void firstIteration(Graph &graph);

void secondIteration(Graph &graph);

Vertex* getOrigin(Graph &graph);

vector<Vertex *> getPickUpLocations(Graph &graph, Vertex* origin);

vector<Vertex *> second_getPickUpLocations(Graph &graph, Vertex* origin, string tag);

vector<Vertex *> getDeliveryLocations(Graph &graph, Vertex* origin);

vector<Vertex *> second_getDeliveryLocations(Graph &graph, Vertex* origin, string tag);

string create_vehicle_tag(map<string, vector<Vertex*>> &totalTags);

vector<NodeInfo> calcOptimalPath(Graph &graph, Vertex* origin,
	vector<Vertex*> locations);

static bool stop = false;
static unsigned int edgeID = 1;

int main() {

	cout << "=========== SECURITY VAN ===========" << endl;
	cout << "Do you wish to load info from provided files? (Y/N)" << endl;
	string nodesFileName, tagsFileName, edgesFileName, coordsFileName;
	string yn;
	bool provided = false;
	srand(time(NULL));

	while (true) {
		cin >> yn;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please insert 'Y' or 'N'." << endl;
			continue;
		}
		if (yn != "Y" && yn != "N") {
			cout << "Please insert 'Y' or 'N'." << endl;
			continue;
		}
		if (yn == "Y") {
			provided = true;
			break;
		}
		break;
	}

	if (provided) {
		cout << "Choose a city to operate in:" << endl;
		cout << "1. Aveiro" << endl;
		cout << "2. Braga" << endl;
		cout << "3. Coimbra" << endl;
		cout << "4. Ermesinde" << endl;
		cout << "5. Fafe" << endl;
		cout << "6. Gondomar" << endl;
		cout << "7. Lisboa" << endl;
		cout << "8. Maia" << endl;
		cout << "9. Porto" << endl;
		cout << "10. Portugal" << endl;
		cout << "11. Viseu" << endl;

		int option = readInputNumber(1, 11);

		nodesFileName = NODES_FILE_NAME;
		tagsFileName = TAGS_FILE_NAME;
		edgesFileName = EDGES_FILE_NAME;
		coordsFileName = COORDS_FILE_NAME;

		string location;

		switch (option) {
		case 1:
			location = "Aveiro";
			break;
		case 2:
			location = "Braga";
			break;
		case 3:
			location = "Coimbra";
			break;
		case 4:
			location = "Ermesinde";
			break;
		case 5:
			location = "Fafe";
			break;
		case 6:
			location = "Gondomar";
			break;
		case 7:
			location = "Lisboa";
			break;
		case 8:
			location = "Maia";
			break;
		case 9:
			location = "Porto";
			break;
		case 10:
			location = "Portugal";
			break;
		case 11:
			location = "Viseu";
			break;
		}

		nodesFileName = nodesFileName + location + ".txt";
		tagsFileName = tagsFileName + location + ".txt";
		edgesFileName = edgesFileName + location + ".txt";
		coordsFileName = coordsFileName + location + ".txt";

	}
	else {
		cout
			<< "Please enter the file name for the nodes (X and Y coordinates): "
			<< endl;
		cout << "-> ";
		getline(cin, nodesFileName);
		cout
			<< "Please enter the file name for the nodes (latitude and longitude): "
			<< endl;
		cout << "-> ";
		getline(cin, coordsFileName);
		cout << "Please enter the file name for the tags: " << endl;
		cout << "-> ";
		getline(cin, tagsFileName);
		cout << "Please enter the file name for the edges: " << endl;
		cout << "-> ";
		getline(cin, edgesFileName);
	}

	Graph graph = loadGraph(nodesFileName, tagsFileName, edgesFileName,
		coordsFileName);

	while (!stop) {
		cout
			<< "Which version of the program do you want to use: (input the appropriate number)"
			<< endl;
		cout << "1 - first iteration: only one vehicle" << endl;
		cout << "2 - second iteration: multiple vehicles for each tag type" << endl;
		int option = readInputNumber(1, 2);

		if (option == 1)
			firstIteration(graph);

		else if (option == 2)
			secondIteration(graph);
	}

	return 0;
}

void firstIteration(Graph &graph) {

	clearGraphVisits(graph);
	Vertex* origin = getOrigin(graph);
	if (origin == NULL)
		return;
	vector<Vertex *> pickUpLocs = getPickUpLocations(graph, origin);
	vector<Vertex *> deliveryLocs = getDeliveryLocations(graph,
		pickUpLocs.at(pickUpLocs.size() - 1));

	vector<NodeInfo> pickUpPath = calcOptimalPath(graph, origin, pickUpLocs);
	if (pickUpPath.size() == 0) {
		cout << "No available route to pass through all pick-up points."
			<< endl;
		return;
	}
	vector<NodeInfo> totalPath;

	if (deliveryLocs.size() == 0) {
		cout << "Route will stop at the last pick-up point (there are no delivery points)." << endl;
		totalPath = pickUpPath;
	}
	else {
		vector<NodeInfo> deliveryPath = calcOptimalPath(graph,
			graph.findVertex(pickUpPath.at(pickUpPath.size() - 1).getID()),
			deliveryLocs);
		if (deliveryPath.size() == 0) {
			cout << "No available route to pass through all delivery points."
				<< endl;
			return;
		}
		totalPath = pickUpPath;
		totalPath.insert(totalPath.end(), deliveryPath.begin() + 1,
			deliveryPath.end());
	}


	double totalWeight = calculatePathLength(totalPath);

	cout << fixed << setprecision(2) << "Total distance(combined weight) traveled: " << totalWeight << endl;
}

void secondIteration(Graph &graph) {

	clearGraphVisits(graph);
	map<string, vector<Vertex*>>::iterator it;
	vector<Vehicle*> vehicles;

	map<string, vector<Vertex*>> totalTags = organizeTags(graph.getVertexSet());

	Vertex* origin = getOrigin(graph);
	if (origin == NULL)
		return;

	while (1) {

		string tag = create_vehicle_tag(totalTags);
		if (tag == string())
			break;
		Vehicle* vetv = new Vehicle(tag);

		vector<Vertex *> pickUpLocs = second_getPickUpLocations(graph, origin, vetv->getTag());
		vetv->setPickUpLocs(pickUpLocs);

		vector<Vertex *> deliveryLocs = second_getDeliveryLocations(graph,
			pickUpLocs.at(pickUpLocs.size() - 1), vetv->getTag());
		vetv->setDeliveryLocs(deliveryLocs);
		vehicles.push_back(vetv);
	}

	for (unsigned int i = 0; i < vehicles.size(); i++) {

		vector<NodeInfo> pickUpPath = calcOptimalPath(graph, origin,
			vehicles.at(i)->getPickUpLocs());
		if (pickUpPath.size() == 0) {
			cout
				<< "No available route to pass through all pick-up points for vehicle with the tag: "
				<< vehicles.at(i)->getTag() << endl;
			continue;
		}

		vector<NodeInfo> totalPath;

		if (vehicles.at(i)->getDeliveryLocs().size() == 0) {
			cout << "Route stops at the last pick-up (there are no deliveries) for the tag: "
				<< vehicles.at(i)->getTag() << endl;
			totalPath = pickUpPath;
		}
		else {
			vector<NodeInfo> deliveryPath = calcOptimalPath(graph,
				graph.findVertex(pickUpPath.at(pickUpPath.size() - 1).getID()),
				vehicles.at(i)->getDeliveryLocs());
			if (deliveryPath.size() == 0) {
				cout
					<< "No available route to pass through all delivery points for vehicle with the tag: "
					<< vehicles.at(i)->getTag() << endl;
				continue;
			}

			totalPath = pickUpPath;
			totalPath.insert(totalPath.end(), deliveryPath.begin() + 1,
				deliveryPath.end());
		}

		double totalWeight = calculatePathLength(totalPath);

		cout << "Total distance(combined weight) traveled by vehicle with the tag: ";
		cout << fixed << setprecision(2) << vehicles.at(i)->getTag() << ": " << totalWeight << endl;
	}

}

Vertex* getOrigin(Graph &graph) {

	cout << "Please enter the coordinates of the starting point:" << endl;
	cout << "Input 0 to quit the program." << endl;
	double lat, lon;
	Vertex* origin = NULL;

	while (1) {
		cout << "Enter latitude:" << endl;
		cout << "-> ";
		lat = readDoubleInputNumber(-90, 90);

		if (lat == 0) {
			stop = true;
			break;
		}

		cout << "Enter longitude:" << endl;
		cout << "-> ";
		lon = readDoubleInputNumber(-180, 180);

		if (lon == 0) {
			stop = true;
			break;
		}

		if (graph.findVertex(lat, lon) != NULL) {
			origin = graph.findVertex(lat, lon);
			origin->setVisited(true);
			break;
		}
		else {
			int randVertex = rand() % graph.getNumVertex();
			cout.unsetf(ios_base::floatfield);
			cout << setprecision(12);
			cout << "Location not found, here is a random suggestion (careful with its usage): " << endl;
			cout << "Latitude: "
				<< graph.getVertexSet().at(randVertex)->getInfo().getLat()
				<< " , Longitude: "
				<< graph.getVertexSet().at(randVertex)->getInfo().getLon() << endl;
		}
	}

	return origin;
}

vector<Vertex *> getPickUpLocations(Graph &graph, Vertex* origin) {

	vector<Vertex *> pickUpLocs;
	double lat, lon;

	cout << "Please enter the coordinates of your pick-up locations:" << endl;
	cout << "Insert 0 otherwise to finish the search." << endl;
	while (1) {
		cout << "Enter latitude:" << endl;
		cout << "-> ";
		lat = readDoubleInputNumber(-90, 90);

		if (lat == 0) {
			if (pickUpLocs.size() == 0) {
				cout << "Pick at least one pick-up location before finishing." << endl;
				continue;
			}
			else
				break;
		}

		cout << "Enter longitude:" << endl;
		cout << "-> ";
		lon = readDoubleInputNumber(-180, 180);

		if (lon == 0) {
			if (pickUpLocs.size() == 0) {
				cout << "Pick at least one pick-up location before finishing." << endl;
				continue;
			}
			else
				break;
		}

		Vertex* v = graph.findVertex(lat, lon);

		if (v == NULL) {
			cout << "Location not found, try again:" << endl;
			cout << "Attempting to find nearby valid points..." << endl;
			if (pickUpLocs.size() == 0)
				suggestPoint(graph, origin, FIRST_ITERATION, EMPTY_STRING_ARGUMENT);
			else
				suggestPoint(graph, pickUpLocs.at(pickUpLocs.size() - 1), FIRST_ITERATION, EMPTY_STRING_ARGUMENT);
			continue;
		}

		if (v->getVisited()) {
			cout
				<< "Location is already picked on the route, can't pick it multiple times."
				<< endl;
			cout << "Attempting to find nearby valid points..." << endl;
			if (pickUpLocs.size() == 0)
				suggestPoint(graph, origin, FIRST_ITERATION, EMPTY_STRING_ARGUMENT);
			else
				suggestPoint(graph, pickUpLocs.at(pickUpLocs.size() - 1), FIRST_ITERATION, EMPTY_STRING_ARGUMENT);
			continue;
		}

		if (v->getInfo().getTag() == "") {
			cout << "Location is not a valid pick-up point (no tag associated)."
				<< endl;
			cout << "Attempting to find nearby valid points..." << endl;
			if (pickUpLocs.size() == 0)
				suggestPoint(graph, origin, FIRST_ITERATION, EMPTY_STRING_ARGUMENT);
			else
				suggestPoint(graph, pickUpLocs.at(pickUpLocs.size() - 1), FIRST_ITERATION, EMPTY_STRING_ARGUMENT);
			continue;
		}

		pickUpLocs.push_back(v);
		v->setVisited(true);
	}

	return pickUpLocs;
}

vector<Vertex *> second_getPickUpLocations(Graph &graph, Vertex* origin, string tag) {

	vector<Vertex *> pickUpLocs;
	double lat, lon;

	cout << "Please enter the coordinates of your pick-up locations:" << endl;
	cout << "Insert 0 otherwise to finish the search." << endl;
	while (1) {
		cout << "Enter latitude:" << endl;
		cout << "-> ";
		lat = readDoubleInputNumber(-90, 90);

		if (lat == 0) {
			if (pickUpLocs.size() == 0) {
				cout << "Pick at least one pick-up location before finishing." << endl;
				continue;
			}
			else
				break;
		}

		cout << "Enter longitude:" << endl;
		cout << "-> ";
		lon = readDoubleInputNumber(-180, 180);

		if (lon == 0) {
			if (pickUpLocs.size() == 0) {
				cout << "Pick at least one pick-up location before finishing." << endl;
				continue;
			}
			else
				break;
		}

		Vertex* v = graph.findVertex(lat, lon);

		if (v == NULL) {
			cout << "Location not found, try again:" << endl;
			cout << "Attempting to find nearby valid points..." << endl;
			if (pickUpLocs.size() == 0)
				suggestPoint(graph, origin, SECOND_ITERATION, tag);
			else
				suggestPoint(graph, pickUpLocs.at(pickUpLocs.size() - 1), SECOND_ITERATION, tag);
			continue;
		}

		if (v->getVisited()) {
			cout
				<< "Location is already picked on the route, can't pick it multiple times."
				<< endl;
			cout << "Attempting to find nearby valid points..." << endl;
			if (pickUpLocs.size() == 0)
				suggestPoint(graph, origin, SECOND_ITERATION, tag);
			else
				suggestPoint(graph, pickUpLocs.at(pickUpLocs.size() - 1), SECOND_ITERATION, tag);
			continue;
		}

		if (v->getInfo().getTag() != tag) {
			cout << "Location is not a valid pick-up point (no tag associated or the tag associated is not valid for the vehicle)."
				<< endl;
			cout << "Attempting to find nearby valid points..." << endl;
			if (pickUpLocs.size() == 0)
				suggestPoint(graph, origin, SECOND_ITERATION, tag);
			else
				suggestPoint(graph, pickUpLocs.at(pickUpLocs.size() - 1), SECOND_ITERATION, tag);
			continue;
		}

		pickUpLocs.push_back(v);
		v->setVisited(true);
	}

	return pickUpLocs;
}

vector<Vertex *> getDeliveryLocations(Graph &graph, Vertex* origin) {

	vector<Vertex *> deliveryLocs;
	double lat, lon;

	cout << "Please enter the coordinates of your delivery locations:" << endl;
	cout << "Insert 0 otherwise to finish the search." << endl;
	while (1) {
		cout << "Enter latitude:" << endl;
		cout << "-> ";
		lat = readDoubleInputNumber(-90, 90);

		if (lat == 0)
			break;

		cout << "Enter longitude:" << endl;
		cout << "-> ";
		lon = readDoubleInputNumber(-180, 180);

		if (lon == 0)
			break;

		Vertex* v = graph.findVertex(lat, lon);

		if (v == NULL) {
			cout << "Location not found, try again:" << endl;
			cout << "Attempting to find nearby valid points..." << endl;
			if (deliveryLocs.size() == 0)
				suggestPoint(graph, origin, FIRST_ITERATION, EMPTY_STRING_ARGUMENT);
			else
				suggestPoint(graph, deliveryLocs.at(deliveryLocs.size() - 1), FIRST_ITERATION, EMPTY_STRING_ARGUMENT);
			continue;
		}

		if (v->getVisited()) {
			cout
				<< "Location is already picked on the route, can't pick it multiple times."
				<< endl;
			cout << "Attempting to find nearby valid points..." << endl;
			if (deliveryLocs.size() == 0)
				suggestPoint(graph, origin, FIRST_ITERATION, EMPTY_STRING_ARGUMENT);
			else
				suggestPoint(graph, deliveryLocs.at(deliveryLocs.size() - 1), FIRST_ITERATION, EMPTY_STRING_ARGUMENT);
			continue;
		}

		if (v->getInfo().getTag() == "") {
			cout
				<< "Location is not a valid delivery point (no tag associated)."
				<< endl;
			cout << "Attempting to find nearby valid points..." << endl;
			if (deliveryLocs.size() == 0)
				suggestPoint(graph, origin, FIRST_ITERATION, EMPTY_STRING_ARGUMENT);
			else
				suggestPoint(graph, deliveryLocs.at(deliveryLocs.size() - 1), FIRST_ITERATION, EMPTY_STRING_ARGUMENT);
			continue;
		}

		deliveryLocs.push_back(v);
		v->setVisited(true);
	}

	return deliveryLocs;
}

vector<Vertex *> second_getDeliveryLocations(Graph &graph, Vertex* origin, string tag) {

	vector<Vertex *> deliveryLocs;
	double lat, lon;

	cout << "Please enter the coordinates of your delivery locations:" << endl;
	cout << "Insert 0 otherwise to finish the search." << endl;
	while (1) {
		cout << "Enter latitude:" << endl;
		cout << "-> ";
		lat = readDoubleInputNumber(-90, 90);

		if (lat == 0)
			break;

		cout << "Enter longitude:" << endl;
		cout << "-> ";
		lon = readDoubleInputNumber(-180, 180);

		if (lon == 0)
			break;

		Vertex* v = graph.findVertex(lat, lon);

		if (v == NULL) {
			cout << "Location not found, try again:" << endl;
			cout << "Attempting to find nearby valid points..." << endl;
			if (deliveryLocs.size() == 0)
				suggestPoint(graph, origin, SECOND_ITERATION, tag);
			else
				suggestPoint(graph, deliveryLocs.at(deliveryLocs.size() - 1), SECOND_ITERATION, tag);
			continue;
		}

		if (v->getVisited()) {
			cout
				<< "Location is already picked on the route, can't pick it multiple times."
				<< endl;
			cout << "Attempting to find nearby valid points..." << endl;
			if (deliveryLocs.size() == 0)
				suggestPoint(graph, origin, SECOND_ITERATION, tag);
			else
				suggestPoint(graph, deliveryLocs.at(deliveryLocs.size() - 1), SECOND_ITERATION, tag);
			continue;
		}

		if (v->getInfo().getTag() != tag) {
			cout << "Location is not a valid delivery point (no tag associated or the tag associated is not valid for the vehicle)."
				<< endl;
			cout << "Attempting to find nearby valid points..." << endl;
			if (deliveryLocs.size() == 0)
				suggestPoint(graph, origin, SECOND_ITERATION, tag);
			else
				suggestPoint(graph, deliveryLocs.at(deliveryLocs.size() - 1), SECOND_ITERATION, tag);
			continue;
		}

		deliveryLocs.push_back(v);
		v->setVisited(true);
	}

	return deliveryLocs;
}

string create_vehicle_tag(map<string, vector<Vertex*>> &totalTags) {

	map<string, vector<Vertex*>>::iterator it;
	cout << "Create a specialized vehicle (VETV), available tags: " << endl;
	vector<string> tags;
	int counter = 1;

	for (it = totalTags.begin(); it != totalTags.end(); it++) {

		cout << "     " << counter << " -> " << it->first << endl;
		tags.push_back(it->first);
		counter++;
	}

	cout << "Input the number of the tag you want to specialize the vehicle in: " << endl;
	cout << "Input 0 to stop adding vehicles." << endl;
	cout << "-> ";
	int option = readInputNumber(0, tags.size());

	if (option == 0)
		return string();
	return tags.at(option - 1);
}

vector<NodeInfo> calcOptimalPath(Graph &graph, Vertex* origin,
	vector<Vertex*> locations) {
	vector<NodeInfo> path;
	vector<NodeInfo> tempPath;
	double pathWeight = 0.0;
	double tempWeight;
	bool skipPermutation = false;

	do {

		for (unsigned int i = 0; i < locations.size(); i++) {

			if (i == 0) {
				graph.dijkstraShortestPath(origin->getInfo());
				tempPath = graph.getPath(origin->getInfo(),
					locations.at(i)->getInfo());
			}
			else {
				vector<NodeInfo> nextPath;
				graph.dijkstraShortestPath(locations.at(i - 1)->getInfo());
				nextPath = graph.getPath(locations.at(i - 1)->getInfo(),
					locations.at(i)->getInfo());
				if (nextPath.size() == 0) {
					skipPermutation = true;
					break;
				}
				tempPath.insert(tempPath.end(), nextPath.begin(),
					nextPath.end());
			}
		}

		if (skipPermutation) {
			skipPermutation = false;
			continue;
		}

		if (pathWeight == 0.0) {
			path = tempPath;
			pathWeight = calculatePathLength(path);
		}
		else {
			tempWeight = calculatePathLength(tempPath);

			if (tempWeight < pathWeight) {
				path = tempPath;
				pathWeight = tempWeight;
			}
		}

	} while (next_permutation(locations.begin(), locations.end()));

	return path;
}

