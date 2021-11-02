#include <iostream>
#include "TicTacTo.hpp"
#include <cstdlib>
using namespace std;

int main(){
    cout << "You are X, Computer is O" << endl;

    tic tac;

    while(tac.checkResult() == -1){
        tac.print();
        tac.player();
        if(tac.checkResult() == -1){
            tac.ai();
        }
    }
    tac.print();
    if(tac.checkResult() == 0){
        cout << "Computer Won" << endl;
    }
    else{
        cout << "Player won" << endl;
    }
}