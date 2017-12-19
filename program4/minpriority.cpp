
    #include "minpriority.h"

  /**
  @Description
  element constructor
  */
    MinPriorityQ::element::element(string in, int Key){
        this->in=in;
        this->Key=Key;
    }

    /**
     @Description
     This function inserts the the new element into min heap,
     then it calls to set the key of this new node to its correct value
     and maintain the min-heap property.


     @param in element to be inserted into min-heap
     @param Key Key to be inserted into min-heap
     */
    void MinPriorityQ::insert(string in,int Key){
      element meanheap(in,Key);
       elem.push_back(meanheap);
        decreaseKey(in, Key);
    }

    /**
     @Description
     This function builds the min heap.
     */

    void MinPriorityQ::buildMinHeap(){
        int size =  (int) (elem.size()-1);
        int s = (size/2);
        for(int i=s;i>=0;i--){
            minHeapify(i);
        }
    }

    /**
     @Description
     This function mantains the min-heap property
     by calling left child and right child.

     @param i the index of the key that violates min-heap property
     */

    void MinPriorityQ::minHeapify(int i){
        int size =  (int) (elem.size()-1);
        int l = left(i)+1;
        int r = right(i)+1;
        int min;
        if(l <=size && elem[l].Key<elem[i].Key){
            min = l;
        }else{
            min = i;
        }
        if(r <=size && elem[r].Key<elem[min].Key){
            min = r;
        }

        if(min!=i){
            swap(i,min);
            minHeapify(min);
        }
    }

    /**
    @Description
    Parent of a node

     @param i index of the heap
     @return 1/2 the parent of index i
     */
    int MinPriorityQ::parent(int i){

        return i/2;
    }

    /**
     @Description
     Left children of index i

     @param i index of the heap
     @return the left children of index i
     */
    int MinPriorityQ::left(int i){

        return 2*i;
    }
    /**
    @Description
    Right children of index i

    @param i index of the heap
    @return the right children of index i
     */
    int MinPriorityQ::right(int i){

        return (2*i) +1;
    }

    /**
    @Description
    This function traverse the heap and it compares an element to its parent,
    exchanging their keys and continuing if the element’s key is larger,
    and terminating if the element’s key is greater,
    since the min-heap property now holds.

     @param id element to be inserted
     @param newKey to be compared and reoreder.
     */

      void MinPriorityQ::decreaseKey(string id,int newKey){

          int index= (int) elem.size()-1;

          if(isMember(id)==true){
          for(int i=0;i<(int) elem.size();i++){
              if(elem[i].in==id){
                  if(newKey<elem[i].Key){
                  elem[i].Key=newKey;
                  index=i;
                  break;
                  }
              }
          }
      }

          while(index>0 && elem[parent(index)].Key>elem[index].Key){
              swap(index,parent(index));
              index = parent(index);
          }

      }


    /**
     @Description
     This function traverse the heap,
     and checks whether the element exists in the heap.

     @param in element to be searched
     @return true if element exists, false if not exists.
     */

    bool MinPriorityQ::isMember(string in){
        for(int i=0;i<(int) elem.size();i++){
            if(elem[i].in==in){
                return true;
            }
        }
        return false;
    }

    /**
     @Description
     This function extracts the smallest element in the heap,
     by removeing the first element and swapping it with the last
     element of the heap to mantain the min-heap property.

     @return the smallest element in the heap.
     */
    string MinPriorityQ::extractMin(){
        int size = (elem.size()-1);
        string min;
        if(size!=-1){
            min = elem[0].in;
            elem[0]=elem[size];
            elem.pop_back();
            minHeapify(0);
        }
        if(size==-1){
            min ="empty";
        }
        return min;
    }
    /**
     @description
     This function swaps the index of an element
     with min.

     @param i index to be swapped.
     @param min min to be swapped.
     */

    void MinPriorityQ::swap(int i, int min){
        element temp =  elem[i];
        elem[i]=elem[min];
        elem[min]=temp;
    }
