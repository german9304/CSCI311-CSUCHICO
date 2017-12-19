/**
 * @file CensusData.h   Declaration of the CensusData class.
 *
 * @author Judy Challinger
 * @date 2/22/13
 */

#ifndef CSCI_311_CENSUSDATA_H
#define CSCI_311_CENSUSDATA_H

#include <vector>
using std::ifstream;
using std::string;
using std::vector;

class CensusData {
public:
   static const int POPULATION = 0;       // type of sort
   static const int NAME = 1;
   ~CensusData();
   void initialize(ifstream&);            // reads in data
   int getSize(){return data.size();}
   void print();                          // prints out data
   void insertionSort(int typesort);      // sorts data using insertionSort
   void mergeSort(int typesort);          // sorts data using mergeSort
   void quickSort(int typesort);          // sorts data using quickSort
private:
   class Record {                         // declaration of a Record
   public:
      string* city;
      string* state;
      int population;
      Record(string&, string&, int);
      ~Record();
   };
   vector<Record*> data;                  // data storage
//
// You may add your private helper functions here!
//
    bool isSmaller(int, Record*, Record*); // this is one I used - you may delete
    /**
    Private helper functions for merge sort
    */
    void MergeSort(int typesort,vector<Record*> & avector,int p,int r);
    void Merge(int typesort,vector<Record*> & avector,int p,int q,int r);
    /**
    Private helper functions for  quickSort sort
    */
    void Randomized_QuickSort(int typesort,vector<Record*> & avector,int p,int r);
    int Randomized_Partition(int typesort,vector<Record*> & avector,int p,int r);
    int Random_Pivot(int p,int r);
    void exchange(int i,int r);
    int partition(int typesort,vector<Record*> & avector,int p,int r);
};

#endif // CSCI_311_CENSUSDATA_H
