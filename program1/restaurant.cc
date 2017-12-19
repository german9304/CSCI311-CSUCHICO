/**
 * @file restaurant.cc
 *
 * @author German Razo
 * @date 2/15/17
 */

#include "restaurant.h"
#include "table.h"
#include<stdio.h>
#include<iostream>
using std::string;

/**
*  @brief
*   This function read from standard input and write to standard output.
*/
void Restaurant::getInput(){
    string in;
    cin>>in;

while(in=="table" || in=="end"|| "party"){

  if(in=="end"){
    break;
  }//if
  if(in=="table"){
    string tableID;
    cin>>tableID;
    int numberSeats;
    cin>>numberSeats;
    string nameServer;
    cin>>nameServer;
    Table * atable = new Table(tableID,numberSeats,nameServer);
    available.append(atable);
  }//if
  if(in=="party"){
    int numberGuests;
    cin>>numberGuests;
    string reservationName;
    cin>>reservationName;
    int timeNeeded;
    cin>>timeNeeded;
    Party * aparty = new Party(reservationName,numberGuests,timeNeeded);
    waiting.append(aparty);
  }//if
  cin>>in;
}//while
}//Getinput()

/**
*  This function Serve Parties for dinners
*/
void Restaurant::serveParties(){
if(available.first()!=nullptr){
  Table * first=available.first();
  Party * firstparty=waiting.first();
  Table * occupiede = occupied.first();
  Table * table = NULL;

  string servername =*(first->getServerName());
  while(waiting.first()!=nullptr || occupied.first()!=nullptr){
    occupiede=occupied.first();
    while(occupiede!=nullptr){
      occupiede->decrementTimer();
      if(occupiede->getTimer()==0){
        cout <<*(occupiede->getParty()->getReservationName())<<" finished at "
        << *(occupiede->getTableID())<<endl;
        int numseat = occupiede->getNumSeats();
        string server = *(occupiede->getServerName());
        string tableid = *(occupiede->getTableID());
        int numguest = occupiede->getParty()->getNumDiners();
        servers[server]+=numguest;
        numguest=0;
        //string * ser  = new string(server);
        // string * tid  = new string(tableid);
        //Table * tempparty= new Table(*(tid ),numseat,*(ser));
        Table * tempparty = new Table(tableid,numseat,server);
        tempparty->seatParty(occupiede->getParty());
        delete tempparty->getParty();
        tempparty->clearTable();
        available.append(tempparty);
        delete occupiede->getParty();
        occupiede= occupied.remove();
      }else{
        occupiede=occupied.next();
      }//if
    }//while
    firstparty=waiting.first();
    while(firstparty!=nullptr){
      for(first=available.first();first!=nullptr;first=available.next()){
        occupiede=occupied.first();
        while(occupiede!=nullptr){
          if(first->getParty()!=nullptr){
            table=first;
          }//if
          occupiede=occupied.next();
        }//while
        if(first->getNumSeats()>= firstparty->getNumDiners() && table!=first){
          first->seatParty(firstparty);
          int numseat = first->getNumSeats();
          string server = *(first->getServerName());
          string tableid = *(first->getTableID());

          //string * ser  = new string(server);
          //string * tid  = new string(tableid);


          Table * tempp = new Table(tableid,numseat,server);
          /**
          Set Table Party
          **/
          tempp->seatParty(firstparty);

          /**
          Set Table Timer
          **/
          tempp->setTimer(firstparty->getTimeRequired());
          /**
          * Print Line when a party is seated.
          */
          cout << *(tempp->getParty()->getReservationName())
          << " seated at " << *(tempp->getTableID()) << endl;

          /**
          *  move table to occupied list
          * Append table to occupied list
          **/
          occupied.append(tempp);
          break;
        }//if
      }//while
      /**
      * If party was seated remove party from waiting list,
      * if parrty was not seated go to the enxt waiting table.
      */
      if(first!=nullptr){
        firstparty=waiting.remove();
      }else{
        firstparty=waiting.next();
      }//if
    }//while
  }//while

    /**
    * Diallocates memory of available parties
    */
    Table * tparty = available.first();
    while(tparty!=NULL){
      delete tparty->getParty();
      tparty = available.next();
    }

    /**
    if no waiting parties and no occupied tables
    print number of diners served by each server
    */
    if(waiting.first()==nullptr && occupied.first()==nullptr){
      map<string,int>::iterator it= servers.begin();
      for (it=servers.begin(); it!=servers.end(); ++it)
      std::cout << it->first << " served " << it->second << '\n';
    }//if
  }//if
}//serve parties()
/**
* main()
*/
int main(){
    /*
     *  Restaurant Object
     */
    Restaurant myDiner;
    myDiner.getInput();
    myDiner.serveParties();

    return 0;
}
