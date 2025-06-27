//
// Created by peyto on 3/13/2025.
//

#include "BoardCalculations.h"
#include <QDebug>
#include <algorithm>

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
    removeSunkenShips(stateCopy);
    /*for(int size : stateCopy->shipSizes){
        qDebug() << size << " ";
    }*/
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
                    BoardState::markAndRemoveShip(j, i, size, newState, vert);

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

void BoardCalculations::removeSunkenShips(BoardState *state)
{
    vector<int> shipSizes = {};
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(state->ships[i][j]){
                int size = isSunkenShip(state, j, i);
                if(size>0) shipSizes.push_back(size);
            }
        }
    }

    for(int size : shipSizes){
        std::vector<int>::iterator position = std::find(state->shipSizes.begin(), state->shipSizes.end(), size);
        if (position != state->shipSizes.end()) // == myVector.end() means the element was not found
            state->shipSizes.erase(position);
    }

}

int BoardCalculations::isSunkenShip(BoardState *state, int x, int y)
{
    if(!state->ships[y][x]) return 0;
    for(int i = max(0,x-1); i<=min(SIZE-1,x+1); i++){
        for(int j = max(0,y-1); j<=min(SIZE-1,y+1); j++){
            //only check tiles above and to the left of (x,y)
            if(!(i>=x && j>=y)){
                //only accept revealed empty tiles
                if(state->ships[j][i] || !state->revealed[j][i]){
                    return 0;
                }
            }
        }
    }

    //check horizontal length
    int shipSize = 1;
    int i = x+1;
    for(;i<SIZE && state->ships[y][i]; i++){
        for(int j = max(0,y-1); j<=min(SIZE-1,y+1); j++){
            if(!state->revealed[j][i]) return 0; //reject if tiles aren't revealed
            if(j==y){
                if(state->ships[j][i]){
                    shipSize++;
                }
            }else{
                if(state->ships[j][i]){
                    return 0; //reject if tiles aren't in a line
                }
            }
        }
    }
    if(i<SIZE){
        for(int j = max(0,y-1); j<=min(SIZE-1,y+1); j++){
            if(!state->revealed[j][i]) return 0;
        }
    }
    if (shipSize>1){
        //make sure no ships are below
        if(y+1<SIZE && state->ships[y+1][x]) return 0;
        return shipSize;
    }

    //do the same with vertical
    i = y+1;
    for(;i<SIZE && state->ships[i][x]; i++){
        for(int j = max(0,x-1); j<=min(SIZE-1,x+1); j++){
            if(!state->revealed[i][j]) return 0; //reject if tiles aren't revealed
            if(j==x){
                if(state->ships[i][j]){
                    shipSize++;
                }
            }else{
                if(state->ships[i][j]){
                    return 0; //reject if tiles aren't in a line
                }
            }
        }
    }
    if(i<SIZE){
        for(int j = max(0,x-1); j<=min(SIZE-1,x+1); j++){
            if(!state->revealed[i][j]) return 0;
        }
    }
    return shipSize;
}








void BoardCalculations::getExpectedEntropy(BoardState* state, double informationDistribution[SIZE][SIZE]){
    double entropyDistribution[SIZE][SIZE];
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            entropyDistribution[i][j] = 0;
            informationDistribution[i][j] = 0;
        }
    }

    auto* stateCopy = new BoardState(state, state->shipSizes);
    removeSunkenShips(stateCopy);

    /*for(int size : stateCopy->shipSizes){
        qDebug() << size << " ";
    }*/

    unsigned long long shipCounts[SIZE][SIZE][SIZE][SIZE];

    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            for(int k = 0; k<SIZE; k++){
                for(int l = 0; l<SIZE; l++){
                    shipCounts[i][j][k][l] = 0;
                }
            }
        }
    }

    getExpectedEntropyHelper(stateCopy, shipCounts, 0, 0);

/*
    //hit distribution given 0,2 is a miss
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            entropyDistribution[i][j] = shipCounts[i][j][i][j] - shipCounts[i][j][0][2];
        }
    }

    //hit distribution given 0,2 is a hit
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            entropyDistributdion[i][j] = shipCounts[0][2][i][j];
        }
    }
*/
    unsigned long long missCounts[SIZE][SIZE][SIZE][SIZE];
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            for(int k = 0; k<SIZE; k++){
                for(int l = 0; l<SIZE; l++){
                    missCounts[k][l][i][j] = shipCounts[i][j][i][j] - shipCounts[i][j][k][l];
                }
            }
        }
    }


   //pHit*entropy|hit + pMiss*entropy|miss
    unsigned long long total = 0;
    unsigned long long int currentShipCounts[SIZE][SIZE];
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            currentShipCounts[i][j] = shipCounts[i][j][i][j];
            total += shipCounts[i][j][i][j];
        }
    }
    total = total/19;

    double pHit;
    double pMiss;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            pHit = shipCounts[i][j][i][j]/(double)total;
            pMiss = (total-shipCounts[i][j][i][j])/(double)total;

            double entropyOfHitState = 0;
            double entropyOfMissState = 0;

            entropyOfHitState = findEntropy(shipCounts[i][j], currentShipCounts[i][j]);
            entropyOfMissState = findEntropy(missCounts[i][j], total-currentShipCounts[i][j]);
            qDebug() << pHit << " " << pMiss;

            entropyDistribution[i][j] = pHit*entropyOfHitState + pMiss*entropyOfMissState;
        }
    }

    double currentEntropy = findEntropy(currentShipCounts, total);

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            informationDistribution[i][j] = currentEntropy-entropyDistribution[i][j];
        }
    }

}


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

//[a][b][c][d] = #of ships on (row c ,col d) given (row a, col b) is a hit
void BoardCalculations::getExpectedEntropyHelper(BoardState* state,  unsigned long long int shipCount[SIZE][SIZE][SIZE][SIZE], int startX, int startY){
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
                if(state->ships[i][j]){
                    for(int k = 0; k<SIZE; k++){
                        for(int l = 0; l<SIZE; l++){
                            shipCount[i][j][k][l] += state->ships[k][l];
                        }
                    }
                }
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
                    BoardState::markAndRemoveShip(j, i, size, newState, vert);

                    //
                    if (only) { getExpectedEntropyHelper(newState, shipCount, 0, 0); }
                    else { getExpectedEntropyHelper(newState, shipCount, j, i); }

                }
            }
        }
        thing = 0;
    }
    delete state;
}
