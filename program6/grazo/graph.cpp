
/***
@Author German Razo Rodriguez
*/
#include "graph.h"
/***
@Brief This function created a vertex object
   it initializes vertex key with 200
   and vertex pi with NIL
@param string name of the vertex
@return none
*/
void Graph::addVertex(string name){
  Vertex av;
  av.Key=200;
  av.pi="NIL";
  vertices[name]=av;
}
/*
 @Brief Adds edges to the graoh

 @param from vertex edge
 @param to vertex edge
 @param weight weight of the eddge of string from vertex to string to vertex
 @return none
 */
void Graph::addEdge(string from,string to,int weight){
  Neighbor an;
  an.name = to;
  an.weight = weight;
  adjList[from].push_back(an);
  Neighbor anen;
  anen.weight = weight;
  anen.name = from;
  adjList[to].push_back(anen);
  std::sort(adjList[from].begin(), adjList[from].end());
}
/**
 @Brief This function creates a minimum spanning tree
 This function of mininmum spannning tree implement's prim's method
 to find the mininum spanning tree between vertices and the least cost weight
 between the edges.
 Vertices get dequeue based on their key, which is the minimum cost weight
 between two vertices, the cost of the edge.
 @param start the root of the spanning tree. 
 @return none
 */
void Graph::mst(string start){
  MinPriorityQ mpq;
  vertices[start].Key=0;  //root key is 0
  mpq.insert(start, vertices[start].Key);
  for(map<string,Vertex>::iterator vert=vertices.begin();
      vert!=vertices.end();++vert){
    if(vert->first!=start){
      mpq.insert(vert->first,vert->second.Key);
    }//if
  }//for
  int totalweight=0;
  string min=mpq.extractMin();
  while(min!="empty"){     //When minqueue is empty, terminate loop
    for(int i=0;i<(int) adjList[min].size();i++){
      if(adjList[min][i].weight<vertices[adjList[min][i].name].Key&&
        mpq.isMember(adjList[min][i].name)!=false){
        vertices[adjList[min][i].name].pi=min;
        vertices[adjList[min][i].name].Key=adjList[min][i].weight;
        mpq.decreaseKey(adjList[min][i].name,adjList[min][i].weight);
      }//if
    }//for
    std::cout<<min<<" "<<vertices[min].pi<<" "<<
    vertices[min].Key<<std:: endl;
    totalweight=vertices[min].Key + totalweight;
    min=mpq.extractMin();
  }//while
  //minimum weight between edges
  std::cout << totalweight << std::endl;
}
