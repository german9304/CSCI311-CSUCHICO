/**
 * @file table.cc
 *
 * @brief
 *    Constructor of Table object
 *
 * @author German Razo
 * @date 2/15/17
 */
#include "table.h"
using namespace std;
#include <iostream>
/**
* Constructor that sets numSeats to a given value.
* Constructor that sets tableID to a given value.
* Constructor that sets serverName to a given value.
* @param numSeats, tableID, serverName
*
*/
Table::Table(const string& tableID, int numSeats, const string& serverName){
this->numSeats=numSeats; this->tableID=new string(tableID);
this->serverName=new string(serverName);}

Table::Table():tableID(NULL),numSeats(0),serverName(NULL){}
Table::~Table(){
  delete tableID;
  delete serverName;
}
  /**
  *
  * @brief
  * This function reads a newParty object as a parameter
  * and assigns it to a new party object
  *
  */
void Table::seatParty(const Party* newParty){
 int timerequired = newParty->getTimeRequired();
 //string * as = new string(*(newParty->getReservationName()));
 string as = *(newParty->getReservationName());
 int numdiners = newParty->getNumDiners();
 Party * ap = new Party(as ,numdiners,timerequired);
 party = ap;
}
