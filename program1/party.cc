/**
 * @file party.cc
 *
 * @brief
 *    Constructor of party object
 *
 * @author German Razo
 * @date 2/15/17
 */

#include "party.h"

  /**
  * Constructor that sets numDiners to a given value.
  * Constructor that sets reservationName to a given value.
  * Constructor that sets timeRequired to a given value.
  * @param reservationName, numDiners, timeRequired
  *
  */
Party::Party( const string& reservationName,int numDiners, int timeRequired){
  this->numDiners=numDiners;
  this->reservationName= new string(reservationName);
  this->timeRequired=timeRequired;
}

Party::~Party(){
 delete reservationName;  
}

Party::Party(){

}
