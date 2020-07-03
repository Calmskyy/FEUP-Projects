#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>
#include <math.h>
#include "Graph.h"
#include "NodeInfo.h"

#define EDGES_FILE_NAME "T08_edges_"
#define NODES_FILE_NAME "T08_nodes_X_Y_"
#define TAGS_FILE_NAME "T08_tags_"
#define COORDS_FILE_NAME "T08_nodes_lat_lon_"

#define FIRST_ITERATION 1
#define SECOND_ITERATION 2
#define EMPTY_STRING_ARGUMENT string()

#define LATITUDE_CONVERSION 110.574
#define LONGITUDE_CONVERSION 111.320
#define PI 3.14159265358979323846

void loadNodes(Graph &graph, std::string fileName);

void loadEdges(Graph &graph, std::string fileName);

void loadTags(Graph &graph, std::string fileName);

void loadCoords(Graph &graph, std::string fileName);

Graph loadGraph(string nodesFileName, string tagsFileName, string edgesFileName, string coordsFileName);

int readInputNumber(int lowNumber, int highNumber);

double readDoubleInputNumber(double lowNumber, double highNumber);

void clearGraphVisits(Graph &graph);

double calculateNodesWeight(double x1, double y1, double x2, double y2);

double calculateKm(double lat1, double lon1, double lat2, double lon2);

double calculatePathLength(vector<NodeInfo> path);

map<string, vector<Vertex*>> organizeTags(const vector<Vertex*> &locations);

void suggestPoint(Graph &graph, Vertex* lastVertex, int iteration, string tag);
