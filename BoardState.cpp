//
// Created by peyto on 2/18/2025.
//

#include "BoardState.h"
using namespace std;
BoardState::BoardState(BoardState *pState) {
for (int i = 0; i<SIZE; i++){
for (int j = 0; j<SIZE; j++){
empty[i][j] = pState->empty[i][j];
ships[i][j] = pState->ships[i][j];
}
}
}

BoardState::BoardState(){
    for (int i = 0; i<SIZE; i++){
        for (int j = 0; j<SIZE; j++){
            empty[i][j] = false;
            ships[i][j] = false;
        }
    }
}
//empty[row][col]
unsigned long int BoardState::getAllBoards(){
    vector<int> shipSizes = {2, 2, 2, 3, 3, 3, 4};
    long int shipCounts[SIZE][SIZE];
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            shipCounts[i][j] = 0;
        }
    }
    auto* stateCopy = new BoardState(this);
    getAllBoardsHelper(shipSizes, stateCopy, shipCounts, 0, 0);
    for (auto & shipCount : shipCounts){
        for (long int & j : shipCount){
            //cout<< j << " ";
        }
        //cout << endl;
    }

    unsigned long int total = 0;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            total+= shipCounts[i][j];
        }
    }
    return total;
}

void BoardState::getAllBoardsHelper(const vector<int>& shipSizes, BoardState* state,  long int shipCount[SIZE][SIZE], int startX, int startY){
    /*for(int x :shipSizes){
        cout << x;
    }
    cout << endl;

    cout << state->toString() << endl;*/
    if(shipSizes.empty()){
        //cout << "AAA" << endl << (state->toString()) << endl;
        for(int i = 0; i<SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                shipCount[i][j] += state->ships[i][j];
            }
        }
        delete state;
        return;
    }
    vector<int> newList = shipSizes;
    int size = newList.back();
    int only = count(newList.begin(), newList.end(), size) == 1;
    newList.pop_back();

    int thing = startX;
    for(int i = startY; i<SIZE; i++){
        for(int j = thing; j<SIZE; j++){

            if(size == 4){
                //cout<<"("<<j <<"," << i << ")";
            }
            if (state->validSpot(j, i,size, false) ){
                //call allboardshelper with new state
                auto* newState = new BoardState(state);
                markShip(j, i, size, newState, false);
                if(only){getAllBoardsHelper(newList, newState, shipCount, 0, 0);}
                else{getAllBoardsHelper(newList, newState, shipCount, j, i);}

            }
            if (state->validSpot(j, i,size, true) ){
                //call allboardshelper with new state
                auto* newState = new BoardState(state);
                markShip(j, i, size, newState, true);
                if(only){getAllBoardsHelper(newList, newState, shipCount, 0,0);}
                else{getAllBoardsHelper(newList, newState, shipCount, j,i);}
            }
        }
        thing = 0;
    }
    delete state;
}

bool BoardState::validSpot(int x, int y, int shipSize, bool vert){
    if(!vert){

        if(x+shipSize>SIZE){return false;}
        for(int i = 0; i<shipSize; i++){
            if(empty[y][x+i]){return false;}

        }
        return true;
    } else{
        if(y+shipSize>SIZE){return false;}

        for(int i = 0; i<shipSize; i++) {
            if (empty[y + i][x]) { return false; }
        }
        return true;
    }

}

void BoardState::markShip(int x, int y, int size, BoardState* state, bool vert) {
    int i = 0;
    int max = size;
    if(!vert) {
        if(x>0){i = -1;}
        if(x+size<SIZE){max++;}
        for (; i < max; i++) {
            state->empty[y][x + i] = true;
            if (y > 0) { state->empty[y - 1][x + i] = true; }
            if (y < SIZE - 1) { state->empty[y + 1][x + i] = true; }
        }
        for (int k = 0; k < size; k++) {
            state->ships[y][x + k] = true;
        }
    } else {
        if(y>0){i = -1;}
        if(y+size<SIZE){max++;}
        for (; i < max; i++) {
            state->empty[y+i][x] = true;
            if (x > 0) { state->empty[y + i][x - 1] = true; }
            if (x < SIZE - 1) { state->empty[y + i][x + 1] = true; }
        }
        for (int k = 0; k < size; k++) {
            state->ships[y + k][x] = true;
        }
    }


}

string BoardState::toString() {
    string output;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if(ships[i][j]){
                output += "x";
            }else if(empty[i][j]){
                output += "o";
            }else{
                output += ".";
            }

        }
        output+="\n";
    }
    return output;
}

void BoardState::setEmpty(int x, int y) {
    empty[y][x] = true;
}


