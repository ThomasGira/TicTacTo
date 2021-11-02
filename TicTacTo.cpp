#include <iostream>
#include "TicTacTo.hpp"
#include <cstdlib>
#include <vector>
#include <stack>
#include <stdio.h>
#include <string.h>
using namespace std;

tic::tic(){
    int game[9];
    for(int i =0 ; i<9; i++){
        board[i] = -1;
        game[i] = -1;
    }
    root = new out(9,true,-1,game,-1);
    root = aiBuild(root);
}
tic::~tic(){
    for(int i =0 ; i<9; i++){
        board[i] = -1;
    }
}

out* tic::aiBuild(out* n){
    if(n->n != 0){
        //cout << "Building" << endl;
        //cout << "possibnle moves: " << n->n << endl;
        int game[9];
        int tempGame[9];
        for(int i=0; i<9;i++){
            game[i] = n->game[i];
        }
        bool loop = true;
        int j = 0;
        
        //cout << "Comparing" << endl;
        if(n->comp == true && n->win == -1){
            //cout << "Guessing Player" << endl;
            for(int i=0; i< n->n; i++){
                //cout << "Possibility " << i << endl;
                loop = true;
                while(loop == true && j<9){
                    if(game[j] == -1){
                        //cout << "Move: " << j << endl;
                        memcpy(tempGame,game,sizeof(tempGame));
                        tempGame[j]=0;
                        //cout << "Result: " << aiResult(tempGame) << endl;
                        //cout << "Player Move: " << j<< endl;
                        child temp;
                        temp.kid = new out(n->n-1,false,aiResult(tempGame),tempGame,j);
                        n->children.push_back(temp);
                        //cout << "Player Built Move: " << n->children[i].kid->move << endl;
                        //cout << "Rebuilding" << endl;
                        if(aiResult(tempGame)==-1){
                            aiBuild(n->children[i].kid);
                        }
                        loop = false;
                    }
                    j++;
                }
            }
        }
        if(n->comp == false && n->win == -1){
            for(int i=0; i< n->n; i++){
                loop = true;
                while(loop == true && j<9){
                    if(game[j] == -1){
                        memcpy(tempGame,game,sizeof(tempGame));
                        tempGame[j]=0;
                        //cout << "AI Result: " << aiResult(tempGame) << endl;
                        //cout << "AI Move: " << j<< endl;
                        child temp;
                        temp.kid = new out(n->n-1,false,aiResult(tempGame),tempGame,j);
                        n->children.push_back(temp);
                        //cout << "AI Built Move: " << n->children[i].kid->move << endl;
                        if(aiResult(tempGame)==-1){
                            aiBuild(n->children[i].kid);
                        }
                        loop = false;
                    }
                    j++;
                }
            }
        }
        //cout << "Built" << endl;
        return n;
    }
}

out* tic::findNode(out* n, int game[9], int level){
    cout << "Finding at level: " << level << endl;
    cout << "Current level: " << n->n << endl;
    int tempGame[9];
    memcpy(tempGame,game,sizeof(tempGame));
    int grid = -1;
    int opp = 0;
    int location;
    if(n->n > level){
        if(n->comp = true){
            opp = 1;
        }
        for(int i= 0; i<9; i++){
            if(tempGame[i] == opp){
                grid = i;
            }
        }
        cout << "Grid: " << grid << endl;
        tempGame[grid] = -1;
        cout << "error check" << endl;
        for(int i=0;i<n->n;i++){
            if(n->children[i].kid->move == grid){
                cout << "Move: " << n->children[i].kid->move << endl;
                location = i;
            }
        }
        return findNode(n->children[location].kid,game,level);
    }
    else{
        cout <<"Found" << endl;
        return n;
    }
}

int tic::bestMove(out* n){
    cout << " Besting" << endl;
    int num = n->n;
    int move;
    int maxWin;
    out* temp;
    vector <int> wins;
    wins.assign(num,0);
    stack <out*> stack;
    for(int i=0; i<num; i++){
        //cout << "Child: " << i << endl;
        stack.push(n->children[i].kid);
        while(!stack.empty()){
            temp = stack.top();
            //cout << "Temp set" << endl;
            stack.pop();
            //cout << "pop" << endl;
            //cout << "Move: " << temp->move << endl;
            if(temp->win != -1){
                if(temp-> win == 0){
                    //cout << "Win" << endl;
                    wins[i] = wins[i] +1;
                }
                else{
                     //cout << "Computer loss" << endl;
                }
            }
            else{
                //cout << "Not Win" << endl;
                //cout << temp->n << " children" << endl;
                for(int j = 0; j<temp->children.size(); j++){
                    //cout << "Push " << j<< endl;
                    stack.push(temp->children[j].kid);
                    //cout << "Adding Move: " << temp->children[j].kid->move << endl;
                }
            }
        }
    }
    cout << "finding max" << endl;
    move = n->children[0].kid->move;
    maxWin = wins[0];
    for(int k = 0; k<num; k++){
        if(wins[k]>maxWin){
            maxWin = wins[k];
            move = n->children[k].kid->move;
        }
    }
    cout << "Bested" << endl;
    return move;
}

void tic::ai(){
    cout << "Thinking" << endl;
    int n = 0;
    for(int i=0; i<9; i++){
        if(board[i] == -1){
            n++;
        }
    }
    int tempBoard[9];
    memcpy(tempBoard,board,sizeof(tempBoard));
    out* node = findNode(root,tempBoard,n);
    int move = bestMove(node);
    if(board[move]==-1){
        board[move] = 0;
    }
    else{
        cout << "I done fucked up" << endl;
    }
    cout << "Thot" << endl;
}

void tic::player(){
    int num;
    bool valid = false;
    while(!valid){
        cout << "Enter number of available location" << endl;
        cin >> num;
        if(num >-1 && num <9){
            if(board[num] == -1){
                valid = true;
            }
            else{
                cout << "ERROR: Selection already occupied" << endl;
            }
        }
        else{
            cout << "ERROR: Invalid Entry" << endl;
        }
    }
    board[num] = 1;
}

void tic::computer(){
    int num;
    int rand();
    bool valid = false;
    while(!valid){
        num = rand()%9;
        if(board[num] == -1){
            valid = true;
        }
    }
    board[num] = 0;
}

void tic::print(){
    for(int i = 0; i<9; i++){
        if(i%3 != 2){
            if(board[i] == -1){
                cout << "(" << i << ")";
            }
            else if(board[i]==0){
                cout << " 0 ";
            }
            else{
                cout << " X ";
            }
            cout << "|";
        }
        else{
            if(board[i] == -1){
                cout << "(" << i << ")";
            }
            else if(board[i]==0){
                cout << " 0 ";
            }
            else{
                cout << " X ";
            }
            cout << endl;
            cout << "------------" << endl;
        }
    }
}

int tic::checkResult(){
    for(int i = 0; i< 3; i++){
        if(board[i*3]==0 && board[i*3+1]==0&&board[i*3+2]==0){
            return 0;
        }
        else if(board[i*3]==1 && board[i*3+1]==1 && board[i*3+2]==1){
            return 1;
        }
    }
    for(int i = 0; i< 3; i++){
        if(board[i]==0 && board[i+3]==0&&board[i+6]==0){
            return 0;
        }
        else if(board[i]==1 && board[i+3]==1 && board[i+6]==1){
            return 1;
        }
    }
    if(board[0] == 0 && board[4] == 0 && board [8] ==0){
        return 0;
    }
    else if(board[2] ==0 && board[4] == 0 && board[6] == 0){
        return 0;
    }
    else if(board[0] == 1 && board[4] == 1 && board [8] == 1){
        return 1;
    }
    else if(board[2] == 1 && board[4] == 1 && board[6] == 1){
        return 1;
    }

    return -1;
}

int tic::aiResult(int game[9]){
    for(int i = 0; i< 3; i++){
        if(game[i*3]==0 && game[i*3+1]==0&&game[i*3+2]==0){
            return 0;
        }
        else if(game[i*3]==1 && game[i*3+1]==1 && game[i*3+2]==1){
            //cout <<"Row" << endl;
            return 1;
        }
    }
    for(int i = 0; i< 3; i++){
        if(game[i]==0 && game[i+3]==0&&game[i+6]==0){
            return 0;
        }
        else if(game[i]==1 && game[i+3]==1 && game[i+6]==1){
            //cout << "collumn" << endl;
            return 1;
        }
    }
    if(game[0] == 0 && game[4] == 0 && game [8] ==0){
        return 0;
    }
    else if(game[2] ==0 && game[4] == 0 && game[6] == 0){
        return 0;
    }
    else if(game[0] == 1 && game[4] == 1 && game [8] == 1){
        return 1;
    }
    else if(game[2] == 1 && game[4] == 1 && game[6] == 1){
        return 1;
    }

    return -1;
}