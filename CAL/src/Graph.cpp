#include "Graph.h"

Vertex::Vertex(NodeInfo in) :
	info(in) {
}

NodeInfo Vertex::getInfo() const {
	return info;
}

void Vertex::setInfo(NodeInfo info) {
	this->info = info;
}

bool Vertex::getVisited() const {
	return visited;
}

void Vertex::setVisited(bool visited) {
	this->visited = visited;
}

void Vertex::addEdge(Vertex *d, double w) {
	adj.push_back(Edge(d, w));
}

bool Vertex::operator<(Vertex & vertex) const {
	return this->dist < vertex.dist;
}

double Vertex::getDist() const {
	return this->dist;
}

Vertex *Vertex::getPath() const {
	return this->path;
}

int Vertex::getAdjSize() const{
	return adj.size();
}

Edge Vertex::getEdge(int ind) const{
	return adj.at(ind);
}

Edge::Edge(Vertex *d, double w) :
	dest(d), weight(w) {
}

Vertex* Edge::getDest() const{
	return dest;
}

int Graph::getNumVertex() const {
	return vertexSet.size();
}

Vertex * Graph::findVertex(const int id) const {
	for (auto v : vertexSet)
		if (v->info.getID() == id)
			return v;
	return NULL;
}

Vertex * Graph::findVertex(const double lat, const double lon) const {
	for (auto v : vertexSet)
		if (v->info.getLat() == lat && v->info.getLon() == lon)
			return v;
	return NULL;
}


bool Graph::addVertex(const NodeInfo &in) {
	if (findVertex(in.getID()) != NULL)
		return false;
	vertexSet.push_back(new Vertex(in));
	return true;
}

bool Graph::addEdge(const int idSource, const int idDest, double w) {
	auto v1 = findVertex(idSource);
	auto v2 = findVertex(idDest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2, w);
	return true;
}

bool Graph::removeEdge(const int idSource, const int idDest) {
	auto v1 = findVertex(idSource);
	auto v2 = findVertex(idDest);
	if (v1 == NULL || v2 == NULL)
		return false;
	return v1->removeEdgeTo(v2);
}

bool Vertex::removeEdgeTo(Vertex *d) {
	for (auto it = adj.begin(); it != adj.end(); it++)
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
	return false;
}

bool Graph::removeVertex(const int id) {
	for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
		if ((*it)->info.getID() == id) {
			auto v = *it;
			vertexSet.erase(it);
			for (auto u : vertexSet) {
				u->removeEdgeTo(v);
			}
			delete v;
			return true;
		}
	}
	return false;
}

vector<NodeInfo> Graph::dfs() const {
	vector<NodeInfo> res;
	for (auto v : vertexSet) {
		v->visited = false;
	}
	for (auto v : vertexSet) {
		if (v->visited == false) {
			dfsVisit(v, res);
		}
	}

	return res;
}

void Graph::dfsVisit(Vertex *v, vector<NodeInfo> & res) const {
	v->visited = true;
	res.push_back(v->info);
	for (auto e : v->adj) {
		auto w = e.dest;
		if (w->visited == false) {
			dfsVisit(w, res);
		}
	}
}

vector<NodeInfo> Graph::bfs(const int idSource) const {
	vector<NodeInfo> res;
	auto s = findVertex(idSource);
	if (s == NULL) {
		return res;
	}
	queue<Vertex *> q;
	q.push(s);
	s->visited = true;
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		res.push_back(v->info);
		for (auto e : v->adj) {
			auto w = e.dest;
			if (w->visited == false) {
				w->visited = true;
				q.push(w);
			}
		}
	}

	return res;
}

vector<NodeInfo> Graph::topsort() const {
	vector<NodeInfo> res;
	for (auto v : vertexSet) {
		v->indegree = 0;
	}
	for (auto v : vertexSet) {
		for (auto e : v->adj) {
			e.dest->indegree++;
		}
	}
	queue<Vertex *> q;
	for (auto v : vertexSet) {
		if (v->indegree == 0) {
			q.push(v);
		}
	}
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		res.push_back(v->info);
		for (auto e : v->adj) {
			auto w = e.dest;
			w->indegree--;
			if (w->indegree == 0) {
				q.push(w);
			}
		}
	}

	if (res.size() != vertexSet.size()) {
		cout << "Graph cannot be ordered this way" << endl;
		res.clear();
	}
	return res;
}

vector<Vertex *> Graph::getVertexSet() const {
	return vertexSet;
}

Vertex * Graph::initSingleSource(const NodeInfo &origin) {
	for (auto v : vertexSet) {
		v->dist = INF; v->path = nullptr;
	}
	auto s = findVertex(origin.getID());
	s->dist = 0;
	return s;
}

bool Graph::relax(Vertex *v, Vertex *w, double weight) {
	if (v->dist + weight < w->dist) {
		w->dist = v->dist + weight;
		w->path = v;
		return true;
	}
	else
		return false;
}

void Graph::dijkstraShortestPath(const NodeInfo &origin) {
	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex> q;
	q.insert(s);
	while (!q.empty()) {
		auto v = q.extractMin();
		for (auto e : v->adj) {
			auto oldDist = e.dest->dist;
			if (relax(v, e.dest, e.weight)) {
				if (oldDist == INF)
					q.insert(e.dest);
				else
					q.decreaseKey(e.dest);
			}
		}
	}
}

vector<NodeInfo> Graph::getPath(const NodeInfo &origin, const NodeInfo &dest) const {
	vector<NodeInfo> res;
	auto v = findVertex(dest.getID());
	if (v == nullptr || v->dist == INF) // missing or disconnected
		return res;
	for (; v != nullptr; v = v->path)
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	return res;
}

Vertex* Graph::getVertex(int ind) {
	return vertexSet.at(ind);
}
