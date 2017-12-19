/**
@File minpriority.h
  @Author German Razo Rodriguez
*/
#ifndef MINPRIORITY_H
#define MINPRIORITY_H
#include <vector>
#include <iostream>
using std::ifstream;
using std::string;

class MinPriorityQ{
public:
    void insert(string id,int Key);
    void decreaseKey(string id,int newKey);
    string extractMin();
    bool isMember(string in);

private:
    class element{
    public:
        element(string in,int Key);
        string in;
        int Key;
    };
    std::vector<element> elem;
    void swap(int i,int min);
    void buildMinHeap();
    void minHeapify(int i);
    int parent(int i);
    int left(int i);
    int right(int i);


};
#endif /* minpriority_h */
