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
unsigned long long int BoardState::getAllBoards(unsigned long long int shipCounts[SIZE][SIZE]){
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            shipCounts[i][j] = 0;
        }
    }
    auto* stateCopy = new BoardState(this, this->shipSizes);
    getAllBoardsHelper(stateCopy, shipCounts, 0, 0);
    //cout << endl;
    /*unsigned long long int max = 0;
    int maxX;
    int maxY;
    for (int i = 0; i<SIZE; i++){
        for (int j = 0; j<SIZE; j++){
            cout<< shipCounts[i][j];
            if(j!=SIZE-1){cout<<", ";}
            if(shipCounts[i][j]>max && !revealed[i][j]){max = shipCounts[i][j]; maxX = j; maxY = i;}
        }
        cout << endl;
    }
    cout << "Most likely: (" << maxX << ", " << maxY << ")" << endl;
*/
    unsigned long long int total = 0;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            total+= shipCounts[i][j];
        }
    }
    return total/SHIPTILES;
}

void BoardState::getAllBoardsHelper(BoardState* state,  unsigned long long int shipCount[SIZE][SIZE], int startX, int startY){
    //base case: Tallies up ship positions if all ships are placed
    if(state->shipSizes.empty()){
        int numShipTiles = 0;
        for(int i = 0; i<SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                numShipTiles += state->ships[i][j];
            }
        }
        if(numShipTiles!=SHIPTILES){
            delete state;return;}
        for(int i = 0; i<SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                shipCount[i][j] += state->ships[i][j];
            }
        }
        delete state;
        return;
    }


    vector<int> newList = state->shipSizes;
    int size = newList.back();

    //checks if there's only one ship of size "Size"
    int only = count(newList.begin(), newList.end(), size) == 1;

    //Iterates through the board placing ship of size "size"
    int thing = startX;
    for(int i = startY; i<SIZE; i++){
        for(int j = thing; j<SIZE; j++){
            for(bool vert : {false, true}) {
                if (state->validSpot(j, i, size, vert)) {
                    //call allboardshelper with new state
                    auto *newState = new BoardState(state, newList);
                    markShip(j, i, size, newState, vert);

                    //
                    if (only) { getAllBoardsHelper(newState, shipCount, 0, 0); }
                    else { getAllBoardsHelper(newState, shipCount, j, i); }

                }
            }
        }
        thing = 0;
    }
    delete state;
}

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



