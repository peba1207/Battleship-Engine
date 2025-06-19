//
// Created by peyto on 2/18/2025.
//

#include "BoardState.h"

#include <utility>
using namespace std;
BoardState::BoardState(BoardState *pState) {
for (int i = 0; i<SIZE; i++){
for (int j = 0; j<SIZE; j++){
    revealed[i][j] = pState->revealed[i][j];
ships[i][j] = pState->ships[i][j];
}
}
shipSizes = pState->shipSizes;
}

BoardState::BoardState(BoardState *pState, vector<int> shipSizes) {
    for (int i = 0; i<SIZE; i++){
        for (int j = 0; j<SIZE; j++){
            revealed[i][j] = pState->revealed[i][j];
            ships[i][j] = pState->ships[i][j];
        }
    }

    this->shipSizes = shipSizes;

}

BoardState::BoardState(){
    for (int i = 0; i<SIZE; i++){
        for (int j = 0; j<SIZE; j++){
            revealed[i][j] = false;
            ships[i][j] = false;
        }
    }

    shipSizes = {2, 2, 2, 3, 3, 3, 4};
}
//revealed[row][col]


bool BoardState::validSpot(int x, int y, int shipSize, bool vert){
    bool allX = true;
    if(!vert){
        if(x+shipSize>SIZE){return false;}

        if(x>0){
            if(y>0){
                if(ships[y-1][x-1]){return false;}
            }
            if(ships[y][x-1]){return false;}
            if(y<SIZE-1){
                if(ships[y+1][x-1]){return false;}
            }
        }
        //y+size<SIZE
        if(x+shipSize<SIZE){
            if(y>0){
                if(ships[y-1][x+shipSize]){return false;}
            }
            if(ships[y][x+shipSize]){return false;}
            if(y<SIZE-1){
                if(ships[y+1][x+shipSize]){return false;}
            }
        }


        for(int i = 0; i<shipSize; i++){
            if(revealed[y][x + i] && !ships[y][x + i]){return false;}
            if(!revealed[y][x + i]){ allX = false;}
            if((y>0 && ships[y-1][x+i]) || (y<SIZE-1 && ships[y+1][x+i])){return false;}
        }
        if(allX){return false;}
        return true;
    } else{

        if(y>0){
            if(x>0){
                if(ships[y-1][x-1]){return false;}
            }
            if(ships[y-1][x]){return false;}
            if(x<SIZE-1){
                if(ships[y-1][x+1]){return false;}
            }
        }
        if(y+shipSize<SIZE){
            if(x>0){
                if(ships[y+shipSize][x-1]){return false;}
            }
            if(ships[y+shipSize][x]){return false;}
            if(x<SIZE-1){
                if(ships[y+shipSize][x+1]){return false;}
            }
        }

        if(y+shipSize>SIZE){return false;}

        for(int i = 0; i<shipSize; i++) {
            if (revealed[y + i][x] && !ships[y + i][x]) { return false; }
            if(!revealed[y + i][x]){ allX = false;}
            if((x>0 && ships[y+i][x-1]) || (x<SIZE-1 && ships[y+i][x+1])){return false;}
        }
        if(allX){return false;}
        return true;
    }

}

void BoardState::markShip(int x, int y, int size, BoardState* state, bool vert) {
    state->shipSizes.erase(find(state->shipSizes.begin(),state->shipSizes.end(),size));
    int i = 0;
    int max = size;
    if(!vert) {
        if(x>0){i = -1;}
        if(x+size<SIZE){max++;}
        for (; i < max; i++) {
            state->revealed[y][x + i] = true;
            if (y > 0) { state->revealed[y - 1][x + i] = true; }
            if (y < SIZE - 1) { state->revealed[y + 1][x + i] = true; }
        }
        for (int k = 0; k < size; k++) {
            state->ships[y][x + k] = true;
        }
    } else {
        if(y>0){i = -1;}
        if(y+size<SIZE){max++;}
        for (; i < max; i++) {
            state->revealed[y + i][x] = true;
            if (x > 0) { state->revealed[y + i][x - 1] = true; }
            if (x < SIZE - 1) { state->revealed[y + i][x + 1] = true; }
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
                output += "x ";
            }else if(revealed[i][j]){
                output += "o ";
            }else{
                output += ". ";
            }

        }
        output+="\n";
    }
    return output;
}

void BoardState::setRevealed(int x, int y) {
    revealed[y][x] = true;
}
void BoardState::setHit(int x, int y) {
    ships[y][x] = true;
}



