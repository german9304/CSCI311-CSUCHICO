/**
 * @file CensusDataSorts.cpp   Sort functions for census population data.
 *
 * @brief
 *    Implements several different types of sorts. Data can be sorted
 * by population or by name of town. This file contains all of the sorting
 * functions and their helpers.
 *
 * @author Judy Challinger
 * @date 2/22/13
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CensusData.h"
#include <chrono>
#include <random>
using std::cout;
using std::endl;

//0 Population
//1 Name
/**
 *  Function Name: insertion Sort
 *
 *  This function sorts the given input using inertion sort algorithm
 *
 *  @param typesort type of record to be sorted
 *
 */
void CensusData::insertionSort(int typesort) {
    int size=getSize();
    Record * Key;
    int i=0;
    int j=0;
        for(int index=0;index<size-1;index++){
            j=index+1;
            Key=data[j];
            i=j-1;
            if(typesort==0){
              while(i>=0&&data[i]->population>Key->population){
                data[i+1]=data[i];
                i=i-1;
              }//while
            data[i+1]=Key;
            }//if
            if(typesort==1){
               while(i>=0&&*(data[i]->city)>*(Key->city)){
                    data[i+1]=data[i];
                    i=i-1;
                }//while
                data[i+1]=Key;
            }//if
        }//for
    return;
}
/**
 *  Function Name: merge Sort
 *
 *  This function sorts the given input using merge sort algorithm
 *
 * @param typesort type of record to be sorted
 *
 */
void CensusData::mergeSort(int typesort) {
     int size = getSize()-1;
     MergeSort(typesort,data,0,size);
     return;
}
/**
 *  Function Name: Merge Sort
 *
 *  This function sorts the given input recursiviely calling itself
 *  using the conquer and divide apporach.
 *
 * @param typesort type of record to be sorted
 * @param avector vector that contains the Records to be sorted
 * @param p First index of the vector that constains the Records
 * @param r Last index of the vector that contains the Records
 *
 */
void CensusData::MergeSort(int typesort,vector<Record*> & avector,int p,int r){
    if(p<r){
        int q=(p+r)/2;
        MergeSort(typesort,avector,p,q);
        MergeSort(typesort,avector,q+1,r);
        Merge(typesort,avector,p,q,r);
    }//if
    return;
}
/**
 *  Function Name: Merge
 *
 * This function creates two vectors with the data to be sorted,
 * one with the left data and one with the right data. Then it combines
 * the two sorted vectors.
 *
 *
 * @param typesort type of record to be sorted
 * @param avector vector that contains the Records to be sorted
 * @param p First index of the vector that constains the Records
 * @param q half index of the vector that contains the Records
 * @param r Last index of the vector that contains the Records
 *
 */
void CensusData::Merge(int typesort,vector<Record*> & avector,int p,int q, int r){
    int n1= q-p +1;
    int n2= r-q;
    int i;
    int j;
    int k;
    vector<Record*> left_Data(n1); //vector with left data
    vector<Record*> right_Data(n2); //vector with right data
    for(i=0;i<n1;i++){
        left_Data[i]=avector[p+i];
    }//for
    for(j=0;j<n2;j++){
        right_Data[j]=avector[q+j+1];
    }//for
    i=0;
    j=0;
    k=p;
    if(typesort==1){
        for(int index=p;index<r;index++){
            if(i<n1 && j<n2){
            if((*(left_Data[i]->city))<=*(right_Data[j]->city)){
                data[k] = left_Data[i];
                k++;
                i++;
            }else{
                data[k]= right_Data[j];
                k++;
                j++;
            }
          }
        }
        while(i<n1){
            data[k]=left_Data[i];
            i++;
            k++;
        }
        while(j<n2){
            data[k]=right_Data[j];
            j++;
            k++;
         }
        }
        if(typesort==0){
           for(int index=p;index<r;index++){
              if(i<n1 && j<n2){
                 if((left_Data[i]->population)<=right_Data[j]->population){
                        data[k] = left_Data[i];
                        k++;
                        i++;
                    }else{
                        data[k]= right_Data[j];
                        k++;
                        j++;
                    }
                }
            }
            while(i<n1){
                data[k]=left_Data[i];
                i++;
                k++;
            }
            while(j<n2){
                data[k]=right_Data[j];
                j++;
                k++;
            }

        }
}
/**
 *  Function Name: quick sort
 *
 *  This function sorts the given input using quick sort algorithm
 *
 * @param typesort type of record to be sorted
 *
 */
void CensusData::quickSort(int typesort) {
        int size = getSize()-1;
        Randomized_QuickSort(typesort,data, 0, size);
}
/**
 *  Function Name: Randomized QuickSort
 *
 *  This function sorts sorts the given input recursiviely calling itself
 *  using the conquer and divide apporach.
 *
 * @param typesort type of record to be sorted
 * @param avector vector that contains the Records to be sorted
 * @param p First index of the vector that constains the Records
 * @param r Last index of the vector that contains the Records
 *
 */
void CensusData::Randomized_QuickSort(int typesort,vector<Record*> & avector,int p,int r){
    if(p<r){
        int q = Randomized_Partition(typesort,avector, p, r);
        Randomized_QuickSort(typesort,avector,p,q-1);
        Randomized_QuickSort(typesort,avector,q+1,r);
    }
}
/**
 *  Function Name: Randomized Partition
 *
 * This function selects a randomly chosen element from the vector
 * and exchanges that element with the last index of the vector,
 * becoming the pivot.
 *
 * @param typesort type of record to be sorted
 * @param avector vector that contains the Records to be sorted
 * @param p First index of the vector that constains the Records
 * @param r Last index of the vector that contains the Records
 * @return the partition
 */
int CensusData::Randomized_Partition(int typesort,vector<Record*> & avector,int p,int r){
    int random_Number= Random_Pivot(p,r);
    exchange(random_Number,r);
    return partition(typesort,avector,p,r);
}
/**
 *  Function Name: Random Pivot
 *
 * This function genereates a random pivot from the length of the vector to be sorted.
 *
 * @param p First index of the vector that constains the Records
 * @param r Last index of the vector that contains the Records
 *
 */
int CensusData::Random_Pivot(int p,int r){
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(p,r);
    int i = distribution(generator);
    return i;
}
/**
 *  Function Name: Partition
 *
 * This function rearranges the vector such that
 * the left elements of the vector are less or equal to the Pivot
 * and right elemnts of the vector are greater than the Pivot.
 *
 * @param typesort type of record to be sorted
 * @param avector vector that contains the Records to be sorted
 * @param p First index of the vector that constains the Records
 * @param r Last index of the vector that contains the Records
 *
 */
int CensusData::partition(int typesort,vector<Record*> & avector,int p,int r){
    string city = *(avector[r]->city);
    int population = avector[r]->population;
    int i=p-1;
    for(int j=p;j<r;j++){
        if(typesort==1){
         if(*(avector[j]->city)<=city){
          i = i+1;
          exchange(i, j);
         }
        }
        if(typesort==0){
           if(avector[j]->population<=population){
             i = i+1;
              exchange(i, j);
            }
        }
      }
    exchange(i+1,r);
    return i+1;
}
/**
 *  Function Name: exchange
 *
 * This function swaps two elements form the vector
 *
 * @param i First index of the vector that constains the Records
 * @param r Last index of the vector that contains the Records
 *
 */
void CensusData::exchange(int i,int r){
    Record * temp_Record=data[r];
    data[r]=data[i];
    data[i]= temp_Record;
}
