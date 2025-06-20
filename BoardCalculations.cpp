//
// Created by peyto on 3/13/2025.
//

#include "BoardCalculations.h"
double BoardCalculations::findEntropy(unsigned long long int shipCounts[SIZE][SIZE], unsigned long long int total){
    if(total == 0){return -1;}
    double entropy = 0;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if(shipCounts[i][j]) entropy+=((double)shipCounts[i][j]/(double)total) * log2((double)total/((double)shipCounts[i][j]));
        }
    }
    //cout<<entropy<<endl;
    return entropy;
}

double BoardCalculations::findExpectedEntropy(int x, int y, BoardState * state, double pHit) {
    auto* stateHit = new BoardState(state);
    stateHit->setHit(x,y);

    unsigned long long int shipCountsHit[SIZE][SIZE];
    for(int i =0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            shipCountsHit[i][j] = 0;
        }
    }

    unsigned long long int hitTotal = getAllBoards(stateHit,shipCountsHit);
    double entropy = pHit* findEntropy(shipCountsHit, hitTotal);

    auto* stateMiss = new BoardState(state);
    stateMiss->setRevealed(x, y);
    unsigned long long int shipCountsMiss[SIZE][SIZE];
    for(int i =0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            shipCountsHit[i][j] = 0;
        }
    }

    unsigned long long int missTotal = getAllBoards(stateMiss,shipCountsMiss);
    entropy += (1-pHit)* findEntropy(shipCountsMiss, missTotal);

    delete stateHit;
    delete stateMiss;
    return entropy;
}

double BoardCalculations::findEntropyOfMiss(int x, int y, BoardState *state) {
    if(state->revealed[y][x]){return 0;}
    auto* stateMiss = new BoardState(state);
    stateMiss->setRevealed(x, y);

    unsigned long long int shipCountsMiss[SIZE][SIZE];

    unsigned long long int missTotal = getAllBoards(stateMiss,shipCountsMiss);
    //cout<< "(" << x << "," << y << ")" <<missTotal << endl;
    double entropy = findEntropy(shipCountsMiss, missTotal);

    delete stateMiss;
    return entropy;
}

double BoardCalculations::findEntropyOfEachTile(BoardState *state, double (*entropyDistribution)[SIZE]) {
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE;j++){
            double entropy = findEntropyOfMiss(j,i,state);
            cout<< "(" << j << "," << i << "): " << entropy<<endl;
            entropyDistribution[i][j] = entropy;
        }
    }
    return 0;
}

void BoardCalculations::printDistribution(double (*distribution)[SIZE]) {
    for (int i = 0; i<SIZE; i++){
        for (int j = 0; j<SIZE; j++){
            cout<< distribution[i][j];
            if(j!=SIZE-1){cout<<", ";}
        }
        cout << endl;
    }
}

void BoardCalculations::printDistribution(unsigned long long int (*distribution)[SIZE]) {
    for (int i = 0; i<SIZE; i++){
        for (int j = 0; j<SIZE; j++){
            cout<< distribution[i][j];
            if(j!=SIZE-1){cout<<", ";}
        }
        cout << endl;
    }
}

unsigned long long int BoardCalculations::getAllBoards(BoardState* state, unsigned long long int shipCounts[SIZE][SIZE]){
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            shipCounts[i][j] = 0;
        }
    }
    auto* stateCopy = new BoardState(state, state->shipSizes);
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

void BoardCalculations::getAllBoardsHelper(BoardState* state,  unsigned long long int shipCount[SIZE][SIZE], int startX, int startY){
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
                    BoardState::markShip(j, i, size, newState, vert);

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