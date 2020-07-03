#include "Utilities.h"
#include <cmath>

Graph loadGraph(string nodesFileName, string tagsFileName, string edgesFileName,
	string coordsFileName) {
	Graph graph;

	cout << "Loading nodes..." << endl;
	loadNodes(graph, nodesFileName);
	cout << "Loading tags..." << endl;
	loadTags(graph, tagsFileName);
	cout << "Loading edges..." << endl;
	loadEdges(graph, edgesFileName);
	cout << "Loading coordinates..." << endl;
	loadCoords(graph, coordsFileName);

	return graph;
}

void loadNodes(Graph &graph, string fileName) {
	ifstream nodesFile;
	nodesFile.open(fileName);

	if (nodesFile.fail()) {
		cerr << "ERROR: nodes file does not exist." << endl;
		exit(1);
	}

	string s;
	int remainingNodes, id;
	bool firstRead = true;
	double x, y;

	while (getline(nodesFile, s)) {
		if (firstRead) {
			remainingNodes = stoi(s);
			firstRead = false;
			continue;
		}

		if (remainingNodes == 0)
			cerr
			<< "ERROR: nodes file had more nodes than declared at the start."
			<< endl;

		stringstream ss(s);
		int counter = 3;

		while (getline(ss, s, ',')) {
			if (s.front() == '(')
				s.erase(s.begin());

			if (s.back() == ')')
				s.erase(s.end() - 1);

			if (isspace(s.front()))
				s.erase(s.begin());

			if (isspace(s.back()))
				s.erase(s.end() - 1);

			if (counter == 3)
				id = stoi(s);
			else if (counter == 2)
				x = stod(s);
			else if (counter == 1)
				y = stod(s);

			counter--;
		}

		NodeInfo info(x, y, id);
		graph.addVertex(info);

		remainingNodes--;
	}

	if (remainingNodes > 0)
		cerr << "ERROR: there were less nodes than declared at the start."
		<< endl;

	nodesFile.close();

}

void loadTags(Graph &graph, string fileName) {
	ifstream tagsFile;
	tagsFile.open(fileName);

	if (tagsFile.fail()) {
		cerr << "ERROR: tags file does not exist." << endl;
		exit(1);
	}

	string s, tag;
	int id, remainingTags;
	int remainingNodes = 0;
	bool firstRead = true;
	bool tagName = false;

	while (getline(tagsFile, s)) {
		if (firstRead) {
			remainingTags = stoi(s);
			firstRead = false;
			continue;
		}

		if (remainingTags == 0)
			cerr
			<< "ERROR: tags file had more nodes than declared at the start."
			<< endl;

		if (!tagName) {
			tag = s;
			tagName = true;
			continue;
		}

		if (remainingNodes > 0) {
			id = stoi(s);
			Vertex* vertex = graph.findVertex(id);
			NodeInfo info = vertex->getInfo();
			info.setTag(tag);
			vertex->setInfo(info);
			remainingNodes--;
			if (remainingNodes == 0) {
				tagName = false;
				remainingTags--;
			}
		}
		else if (remainingNodes == 0)
			remainingNodes = stoi(s);

	}

	if (remainingTags > 0)
		cerr << "ERROR: there were less tags than declared at the start."
		<< endl;

	tagsFile.close();

}

void loadEdges(Graph &graph, string fileName) {
	ifstream edgesFile;
	edgesFile.open(fileName);

	if (edgesFile.fail()) {
		cerr << "ERROR: edges file does not exist." << endl;
		exit(1);
	}

	string s;
	int remainingEdges, idSource, idDest;
	bool firstRead = true;
	double x1, y1, x2, y2, w;

	while (getline(edgesFile, s)) {
		if (firstRead) {
			remainingEdges = stoi(s);
			firstRead = false;
			continue;
		}

		if (remainingEdges == 0)
			cerr
			<< "ERROR: edges file had more edges than declared at the start."
			<< endl;

		stringstream ss(s);
		int counter = 2;

		while (getline(ss, s, ',')) {
			if (s.front() == '(')
				s.erase(s.begin());

			if (s.back() == ')')
				s.erase(s.end() - 1);

			if (isspace(s.front()))
				s.erase(s.begin());

			if (isspace(s.back()))
				s.erase(s.end() - 1);

			if (counter == 2)
				idSource = stoi(s);
			else if (counter == 1)
				idDest = stoi(s);
			counter--;
		}

		Vertex* source = graph.findVertex(idSource);
		Vertex* dest = graph.findVertex(idDest);
		x1 = source->getInfo().getX();
		y1 = source->getInfo().getY();
		x2 = dest->getInfo().getX();
		y2 = dest->getInfo().getY();
		w = calculateNodesWeight(x1, y1, x2, y2);
		graph.addEdge(idSource, idDest, w);
		remainingEdges--;
	}

	if (remainingEdges > 0)
		cerr << "ERROR: there were less edges than declared at the start."
		<< endl;

	edgesFile.close();
}

void loadCoords(Graph &graph, std::string fileName) {
	ifstream coordsFile;
	coordsFile.open(fileName);

	if (coordsFile.fail()) {
		cerr << "ERROR: coordinates file does not exist." << endl;
		exit(1);
	}

	string s;
	int id, remainingCoords;
	bool firstRead = true;
	double lat, lon;

	while (getline(coordsFile, s)) {
		if (firstRead) {
			remainingCoords = stoi(s);
			firstRead = false;
			continue;
		}

		if (remainingCoords == 0)
			cerr
			<< "ERROR: coordinates file had more coordinates than declared at the start."
			<< endl;

		stringstream ss(s);
		int counter = 3;

		while (getline(ss, s, ',')) {
			if (s.front() == '(')
				s.erase(s.begin());

			if (s.back() == ')')
				s.erase(s.end() - 1);

			if (isspace(s.front()))
				s.erase(s.begin());

			if (isspace(s.back()))
				s.erase(s.end() - 1);

			if (counter == 3)
				id = stoi(s);
			else if (counter == 2)
				lat = stod(s);
			else if (counter == 1)
				lon = stod(s);

			counter--;
		}
		Vertex* vertex = graph.findVertex(id);
		NodeInfo info = vertex->getInfo();
		info.setLat(lat);
		info.setLon(lon);
		vertex->setInfo(info);

		remainingCoords--;
	}

	if (remainingCoords > 0)
		cerr << "ERROR: there were less coordinates than declared at the start."
		<< endl;

	coordsFile.close();

}

int readInputNumber(int lowNumber, int highNumber) { // used to input a number, restricted by menu options

	int numberInput;

	while (1) {
		std::cin >> numberInput;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(200, '\n');
			std::cout << "Please input a valid number: ";
			continue;
		}
		if (numberInput < lowNumber || numberInput > highNumber) {
			std::cout << "Please input a single number between " << lowNumber
				<< " and " << highNumber << " (inclusive): ";
			std::cin.clear();
			std::cin.ignore(200, '\n');
			continue;
		}
		break;
	}
	return numberInput;
}

double readDoubleInputNumber(double lowNumber, double highNumber) { // used to input a number (double), restricted by menu options

	double numberInput;

	while (1) {
		std::cin >> numberInput;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(200, '\n');
			std::cout << "Please input a valid number: ";
			continue;
		}
		if (numberInput < lowNumber || numberInput > highNumber) {
			std::cout << "Please input a single number between " << lowNumber
				<< " and " << highNumber << " (inclusive): ";
			std::cin.clear();
			std::cin.ignore(200, '\n');
			continue;
		}
		break;
	}
	return numberInput;
}

void clearGraphVisits(Graph &graph) {

	for (unsigned int i = 0; i < graph.getVertexSet().size(); i++) {

		graph.getVertexSet().at(i)->setVisited(false);
	}
}

double calculateNodesWeight(double x1, double y1, double x2, double y2) {
	double a = pow(x1 - x2, 2);
	double b = pow(y1 - y2, 2);
	return sqrt(a + b);
}

double calculateKm(double lat1, double lon1, double lat2, double lon2) {
	double a = pow(lat1 - lat2, 2);
	double b = pow(lon1 - lon2, 2);

	double latitude_radian = lat2 * PI / 180;
	b = b / (LONGITUDE_CONVERSION * cos(latitude_radian));
	a = a / LATITUDE_CONVERSION;
	return sqrt(a + b);
}

double calculatePathLength(vector<NodeInfo> path) {

	double totalWeight = 0.0;

	for (unsigned int i = 1; i < path.size(); i++) {

		double weight = calculateNodesWeight(path.at(i - 1).getLat(),
			path.at(i - 1).getLon(), path.at(i).getLat(), path.at(i).getLon());
		totalWeight += weight;
	}

	return totalWeight;
}

map<string, vector<Vertex*>> organizeTags(const vector<Vertex*> &locations) {

	map<string, vector<Vertex*>> m;
	map<string, vector<Vertex*>>::iterator it;

	for (unsigned int i = 0; i < locations.size(); i++) {

		Vertex* v = locations.at(i);
		if (v->getInfo().getTag().length() == 0)
			continue;

		it = m.find(v->getInfo().getTag());

		if (it == m.end()) {
			vector<Vertex*> newVector;
			newVector.push_back(v);
			m.insert({ v->getInfo().getTag(), newVector });
		}
		else {
			it->second.push_back(v);
		}
	}

	return m;
}

void suggestPoint(Graph &graph, Vertex* lastVertex, int iteration, string tag) {

	map<string, vector<Vertex*>> tagsVertex = organizeTags(
		graph.getVertexSet());
	map<string, vector<Vertex*>>::iterator it;
	vector<NodeInfo> tempPath;

	for (it = tagsVertex.begin(); it != tagsVertex.end(); it++) {

		if (iteration == SECOND_ITERATION)
			if (it->first != tag)
				continue;

		double weight = 0.0;
		double tempWeight;
		Vertex* finalVertex = NULL;
		int counter = 0;
		for (unsigned int i = 0; i < it->second.size(); i++) {

			Vertex* v = it->second.at(i);

			graph.dijkstraShortestPath(lastVertex->getInfo());
			tempPath = graph.getPath(lastVertex->getInfo(), v->getInfo());

			tempWeight = calculatePathLength(tempPath);

			if (weight < tempWeight && tempPath.size() != 0
				&& v->getVisited() == false) {
				weight = tempWeight;
				finalVertex = v;
			}
		}

		cout.unsetf(ios_base::floatfield);
		cout << setprecision(12);

		if (weight != 0.0 && finalVertex != NULL) {
			cout << "Tag: " << it->first << " -> Latitude: "
				<< finalVertex->getInfo().getLat() << " , Longitude: " << finalVertex->getInfo().getLon();
			cout << fixed << setprecision(2) << " , Distance: " << weight << endl;
		}
		else
			cout << "No valid point found for the tag: " << it->first << endl;

	}
}

