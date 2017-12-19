/**
@File graph.h
  @Author German Razo Rodriguez 
*/
#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <map>
#include <vector>
#include "minpriority.h"
#include <algorithm>
using std::string;
using std::map;
using std::vector;

class Graph{
public:
    void addVertex(string name);
    void addEdge(string from,string to,int weight);
    void mst(string start);
    void print();
private:
    class Vertex{
    public:
        string pi;
        int Key;
    };
    class Neighbor{
    public:
        string name;
        int weight;
   bool operator<(const Neighbor& n) const { return name < n.name; }
    };
    map<string,Vertex> vertices;
    map<string,vector<Neighbor>> adjList;
    MinPriorityQ minQ;
};

#endif /* graph_h */
