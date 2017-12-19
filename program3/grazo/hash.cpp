  #include "hash.h"
  #include <iostream>
  #include<fstream>
  #include<sstream>
  using std::cout;
  using std::ifstream;
  using std::ios;
  using std::endl;

  /*
  @Description
  Constructor of hash function
  **/

  Hash::Hash(){
    collisions=0;
    longestList=0;
    runningAvgListLength=0.0;
  }

  /**
   @Description
   This function removes for the input string given from the user

   @param in a string input from user
   */
  void Hash::remove(string in){
    int s = hf(in);
    for(std::list<string>::iterator it=hashTable[s].begin();it!=hashTable[s].end();++it){
      if((*it)==in){
        hashTable[s].remove(in);
        runningAvgListLength = (currentAvgListLen() + runningAvgListLength) / 2.0;
        return;
      }
    }
  }

  /**
  @Description
  Prints the hash table standard output (cout)
  */
  void Hash::print(){
    for(int i=0;i<HASH_TABLE_SIZE;i++){
      if(!hashTable[i].empty()){
        std::list<string>::iterator it=hashTable[i].begin();
        cout <<i << ":\t" <<*(it) << ", ";
        ++it;
        while(it != hashTable[i].end()){
          cout <<*(it) << ", ";
          ++it;
        }
        cout << endl;
      }else{
        cout <<i << ":\t" << endl;
     }
    }
  }

  /*
  @Descritpion
  Add all of the words in the file specified as "filename" to the hash table.

  */
  void Hash::processFile(string in){
    ifstream fin;
    fin.open(in.c_str(), ios::in); // opens file for reading
    string line;
    getline(fin, line);
    int i=0;
    while(!fin.eof()){
      int h= hf(line);
      if(hashTable[h].empty()){
        hashTable[h].push_front(line);
        runningAvgListLength =(currentAvgListLen() + runningAvgListLength) / 2.0;
      }else{
        hashTable[h].push_back(line);
        runningAvgListLength = (currentAvgListLen() + runningAvgListLength) / 2.0;
        collisions++;
      }
      getline(fin, line);
      i++;
    }
    longestlist();
    fin.close();
    return;
  }

  /**
   @Description
   This function searchs for the input string given from the user

   @param in a string input from user
   @return true, if string word is found found and false if it not found.
   */
  bool Hash::search(string in){
    int s = hf(in);
    for(std::list<string>::iterator it=hashTable[s].begin();it!=hashTable[s].end();++it){
      if((*it)==in){
        return true;
      }
    }
    return false;
  }

  /**
   @Descritpion
   This function keeps track of the length of the longest list ever generated
   and updates after every insert.
   */
  void Hash::longestlist(){
    for(int i=0;i<HASH_TABLE_SIZE;i++){
      unsigned int hashsize =hashTable[i].size();
      if(!hashTable[i].empty() && hashTable[i].size()>1){
        if(longestList<hashsize){
          longestList=hashsize;
        }
      }
    }
  }

  /**
   @Descritpion
   Keeps track of the running average list length,
   and after each successful remove and or remove operation
   it determines the current average list length of the hash table.

   @return avg, returns the running average list lenght.
   */

  double Hash::currentAvgListLen(){
    double hashsize =0;
    double nonEmpty=0.0;
    double avg=0.0;
    for(int i=0;i<HASH_TABLE_SIZE;i++){
      hashsize += hashTable[i].size();
      if(!hashTable[i].empty()){
        nonEmpty++;
      }
    }
    avg = (hashsize/nonEmpty);
    loadfactor= hashsize/HASH_TABLE_SIZE;
    return avg;
  }
  /*
  @Descritpion
   Output the hash table to the file specified as "filename."

  */
  void Hash::output(string in){
    std::ofstream fout;
    fout.open(in);
    for(int i=0;i<HASH_TABLE_SIZE;i++){
      if(!hashTable[i].empty()){
        std::list<string>::iterator it=hashTable[i].begin();
        fout <<i << ":\t" <<*(it) << ", ";
        ++it;
        while(it != hashTable[i].end()){
          fout <<*(it) << ", ";
          ++it;
        }
        fout << endl;
      }else{
        fout <<i << ":\t" << endl;
      }
    }
     fout.close();
  }
  /**
  @Descritpion
  Prints the stats of the hash table

  */

  void Hash::printStats(){
    cout << "Total Collisions = " << collisions << endl;
    cout << "Longest List Ever = " << longestList << endl;
    cout << "Average List Length Over Time = " << runningAvgListLength << endl;
    cout << "Load Factor = " << loadfactor << endl;

  }
