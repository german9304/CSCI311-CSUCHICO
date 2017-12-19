/**
@Brief In this assignment you will implement Prim's algorithm
for generating a Minimum Spanning Tree (MST).
@Author German Razo Rodriguez
*/
#include <stdio.h>
#include "mstapp.h"
#include <sstream>
using std::cin;
using std::cout;
using std::endl;
/*******
@Description This function eads a weighted undirected graph from stdin and
 writes the structure of the MST to stdout.
@return none
***/
void MSTapp::readGraph(){
  Graph agraph;
  string name;
  string first;
  getline(cin,name);
  vector<string> vertices;
  string temp="";
  for(int i=0;i<(int) name.length()+1;i++){
    if(name[i]!=' '&&name[i]!='\0'){
      temp+=name[i];
    }else{
      if(temp!=""){
        vertices.push_back(temp);
        temp="";
      }
    }
  }
  for(int index=0;index<(int) vertices.size();index++){
    if(index==0){
      first=vertices[index];
      agraph.addVertex(first);
    }else{
      agraph.addVertex(vertices[index]);
    }
  }
  string from,to;
  int weight;
  while(!cin.eof()){
    cin>>from>>to>>weight;
    agraph.addEdge(from,to,weight); //Adds edges to the graph
  }
  agraph.mst(first);  //root of the MST(first)
}

int main(){
    MSTapp amst;
    amst.readGraph();
    return 0;
}
