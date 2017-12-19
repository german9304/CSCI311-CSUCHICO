/**
@File
  This program allows the user to enter commands to insert, delete,
  and find key-value pairs in a red-black tree.
  There is also a command to print the tree.
   Each command is entered on a separate line.
rapp.cpp
@Author German Razo Rodriguez
@Date 04/29/2017
*/
#include "rbapp.h"
#include <stdio.h>
#include <iostream>
#include <vector>
using std::string;
using std::cout;
using std::endl;
using std::cin;
/**
 @brief This function allows user to enter commands
 and it if quit is received the function returns to main

 @param none
 @return none
 **/
void RBapp::mainLoop(){
  string insert;
  while(!cin.eof()){
    cin>>insert;
    bool b = processCommand(insert);
    if(b==false){
      break;
    }
    insert=" ";
  }
}
/**
 @brief This function process commands, insert, delete, print and find.

 @param in the string in is the command to be processed
 @return  true if quit command is not inserted, otherwise return true
 **/
bool RBapp::processCommand(string& in){
    if(in=="insert"){
        std::cin >> in;
        processInsert(in);
        return true;
    }else if(in=="find"){
        std::cin >> in;
        processFind(in);
        return true;
    }else if(in=="print"){
        processPrint();
        return true;
    } else if(in=="delete"){
        std::cin >> in;
        processDelete(in);
        return true;
    }else{
      return false;
    }
    if(in=="quit"){
    return false;
    }
    return false;
}
/**
 @brief this function process insert command
 This function calls rbInsert to insert the node entered by user
 into the red black tre.
 @param in string in to be inserted , a key and value
 @return none
 **/
void RBapp::processInsert(string& in){
    string key=in;
    getline(std::cin,in);
    string data=in;
    data.erase(0,1);
    myRBT.rbInsert(key,data);
}
/**
 @brief this function process find command
 This function calls rbFind to find the key entered by user,
 in the red black tree
 It then prints all the nodes that were found in the red black tree.
 @param in string in to be found, a key.
 @return none
 **/
void RBapp::processFind(string& in){
    string key=in;
    vector<const string*> av;
    av=myRBT.rbFind(key);
    for(int i=0;i<(int) av.size();i++){
        std::cout<<key<<" "<<*(av[i])<<std::endl;
     }
}
/*
 @Brief This function calls rbPrintTree to print the red black tree

 @param none
 @return none
 **/
void RBapp::processPrint(){
    myRBT.rbPrintTree();
}
/**
 @brief this function process delete  command
 This function calls rbDelete to delete the node in the red black tree
 It calls rbDelete to delete the node,
 with the key and value enter form user.
 @param in string in to be found, a key.
 @return none
 **/
void RBapp::processDelete(string& in){
    string key = in;
    getline(std::cin,in);
    string data = in;
    data.erase(0,1);
    myRBT.rbDelete(key,data);
}
int main(void){
    RBapp RBapp;      //RBapp Object
    RBapp.mainLoop();
    return 0;
}
