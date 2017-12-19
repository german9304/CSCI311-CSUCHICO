
/**

@Assignment Minimum-Priority Queue

@Author German Razo
04/15/2017
*/
#include <iostream>
#include "minpriority.h"
using std::cin;

void inputfile(){

    MinPriorityQ ap;
    string id;
    int key;
    string input;
    std::cin>>input;
    while(input=="a" || input=="x" || input=="d"){
        if(input=="a"){
            cin >>id;
            cin>>key;
            ap.insert(id, key);
        }
        if(input=="x"){
            string min = ap.extractMin();
            std::cout << min << std::endl;
        }
        if(input=="d"){
            cin >>id;
            cin>>key;
            ap.decreaseKey(id, key);
        }
        cin>>input;
    }
    if(input=="quit"){
        return;
    }

}

int main() {
  /**
  @Description
  This function process the commands
  that are input from the user.

  */
    inputfile();
    return 0;
}
