/* This assignment originated at UC Riverside.*/
 /**

 @author German Razo
 */
#include <string>
#include "hash.h"
#include <iostream>
#include <chrono>
#include <random>
#include <math.h>

using std::string;
using std::cout;
using std::endl;
// This is only a sample hash function (and a bad one at that). You will
// need to replace the contents of this hash function with your own
// hash function

/**
 @Description
 Hash functions assume that keys are natural numbers, however,
 this hash function takes an string of five characters as an input, so
 we must take an approach to index this input in the hash table.
 To resolve this issue, this function represents every character
 as a natural number using the ASCii table.
 The function splits the string of 5 characters into 2, 2 and 1.
 For example,
 given string: "takes" this function splits it into total = (t+a) + (k+e) + s.

 The first 2 characters are added and multiplied by the numbers 63
 and number 17, and the result is stored in the variable res_1.

 The next 2 characters are added and multiplied by the numbers 46,
 and prime number 23, and the result is stored in the variable res_2.

 The last character of the string is multiplied by the prime number 53
 ,mod by prime number 59 and multiplied by prime number 31.

 Then, after getting the resuls of these additions it adds
 the variables res_1, res_2, and res_3 and stores the result in variable total.
 Finally, it mods the result with the HASH_TABLE_SIZE, total%HASH_TABLE_SIZE.
 I created this function because it performs a good random distribution
 throughout the hash table with the use of prime numbers. All the operations
 performed in the function help to create random numbers to be spread,
 with operations like adding, subtracting and multiplication.
 The goal was to perfom a good distribution ,so this is how I created my own function.

 @param ins string of five letters
 @return an integer that will be the index of the given input in the hash table.
 */

 int Hash::hf(string ins) {
   int res_1=0;
   int res_2=0;
   int res_3=0;
   for(int i=0;i<2;i++){
     res_1 = (res_1 + (((int) ins[i]))*(63))*17; //first two letters
     res_2 = ((res_2 + ((int) ins[(i+2)])*46)*23); //next two letters
   }
   res_3=((((int) ins[4] *53)%59)*31); //last letter
   int total=(res_1 + res_2 + res_3);
   int h1 = (total % HASH_TABLE_SIZE);
   return h1;
 }
