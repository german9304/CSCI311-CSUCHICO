Node * xr = root;
   Node * z = rbTreeSearch(xr, key);
   if(z!=nil){
       Node * succ=rbTreeSuccessor(z);
       Node * pred=rbTreePredecessor(z);
       Node * tempsucct=nullptr;
       Node * tempsucc=nullptr;
       Node * temppredd=nullptr;
       Node * temppreddt=nullptr;

       while(succ!=nil || pred!=nil){

           if(succ!=nil){
           if(*(succ->key)==key){
               if(*(succ->value)==value){
                   Node * temp =succ;
                   rbDelete(succ);
                   delete temp;
               tempsucct=rbTreeSuccessor(z);
               succ=tempsucct;
               }else{
               tempsucc=rbTreeSuccessor(succ);
               succ=tempsucc;
               }
           }else{
               succ=nil;
            }
           }

           if(pred!=nil){
               if(*(pred->key)==key ){
                   if(*(pred->value)==value){
                       Node * tempPr =pred;
                       rbDelete(pred);
                       delete tempPr;
                       temppredd=rbTreePredecessor(z);
                       pred=temppredd;
                   }else{
                       temppreddt=rbTreePredecessor(pred);
                       pred=temppreddt;
                   }

               }else{
                   pred=nil;
               }
           }
       }
       Node * tempz = z;
       rbDelete(z);
       delete tempz;
   }
