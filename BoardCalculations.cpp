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

    unsigned long long int hitTotal = stateHit->getAllBoards(shipCountsHit);
    double entropy = pHit* findEntropy(shipCountsHit, hitTotal);

    auto* stateMiss = new BoardState(state);
    stateMiss->setRevealed(x, y);
    unsigned long long int shipCountsMiss[SIZE][SIZE];
    for(int i =0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            shipCountsHit[i][j] = 0;
        }
    }

    unsigned long long int missTotal = stateMiss->getAllBoards(shipCountsMiss);
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

    unsigned long long int missTotal = stateMiss->getAllBoards(shipCountsMiss);
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

