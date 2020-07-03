#pragma once

#include <vector>
#include <queue>
#include <iostream>
#include <limits>
#include <list>
#include <algorithm>
#include "NodeInfo.h"
#include "MutablePriorityQueue.h"
using namespace std;

#define INF std::numeric_limits<double>::max()

class Vertex;
class Edge;
class Graph;

class Vertex {
	NodeInfo info;         // contents
	vector<Edge> adj;      // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	int indegree;          // auxiliary field used by topsort
	bool processing;       // auxiliary field used by isDAG
	double dist = 0;
	Vertex *path = NULL;
	int queueIndex = 0;
	void addEdge(Vertex *dest, double w);
	bool removeEdgeTo(Vertex *d);
public:
	Vertex(NodeInfo info);
	friend class Graph;
	NodeInfo getInfo() const;
	void setInfo(NodeInfo info);
	bool getVisited() const;
	void setVisited(bool visited);
	bool operator<(Vertex & vertex) const;
	double getDist() const;
	Vertex *getPath() const;
	friend class MutablePriorityQueue<Vertex>;
	int getAdjSize() const;
	Edge getEdge(int ind) const;
};

class Edge {
	Vertex * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex *d, double w);
	friend class Graph;
	friend class Vertex;
	Vertex* getDest() const;
};

class Graph {
	vector<Vertex*> vertexSet;    // vertex set

	void dfsVisit(Vertex *v, vector<NodeInfo> & res) const;
public:
	Vertex *findVertex(const int id) const;
	Vertex *findVertex(const double lat, const double lon) const;
	int getNumVertex() const;
	bool addVertex(const NodeInfo &in);
	bool removeVertex(const int id);
	bool addEdge(const int idSource, const int idDest, double w);
	bool removeEdge(const int idSource, const int idDest);
	vector<NodeInfo> dfs() const;
	vector<NodeInfo> bfs(const int idSource) const;
	vector<NodeInfo> topsort() const;
	vector<Vertex *> getVertexSet() const;
	//DJIKSTRA
	void dijkstraShortestPath(const NodeInfo &origin);
	vector<NodeInfo> getPath(const NodeInfo &origin,
		const NodeInfo &dest) const;
	Vertex * initSingleSource(const NodeInfo &orig);
	bool relax(Vertex *v, Vertex *w, double weight);
	Vertex* getVertex(int ind);
};

