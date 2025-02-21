#include <iostream>
#include "BoardState.h"
double findEntropy(unsigned long long int shipCounts[SIZE][SIZE], unsigned long long int total){
    if(total == 0){return 0.;}
    double entropy = 0;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if(shipCounts[i][j]) entropy+=((double)shipCounts[i][j]/(double)total) * log2((double)total/((double)shipCounts[i][j]));
        }
    }
    cout<<entropy<<endl;
    return entropy;
}

double findExpectedEntropy(int x, int y, BoardState * state, double pHit) {
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
    stateMiss->setEmpty(x,y);
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
int main() {
    std::cout << "Hello, World!" << std::endl;
    auto *test = new BoardState();
    test->setEmpty(1,0);
    unsigned long long int shipCounts[SIZE][SIZE];
    //initializes to 0s


    for(int i =0; i<SIZE; i++){for(int j = 0; j<SIZE; j++){shipCounts[i][j] = 0;}}

    unsigned long long int total = test->getAllBoards(shipCounts);
    for(int i = 1; i<SIZE; i++){
        for(int j = 0; j<SIZE;j++){
            double pHit = (double)shipCounts[i][j]/(double)total;
            double entropy = findExpectedEntropy(j,i,test, pHit);
            cout<< "(" << j << "," << i << "): " << entropy<<endl;
        }
    }
    delete test;

    test = new BoardState();
    test->setHit(1,0);
    total = test->getAllBoards(shipCounts);

    for(int i = 1; i<SIZE; i++){
        for(int j = 0; j<SIZE;j++){
            double pHit = (double)shipCounts[i][j]/(double)total;
            double entropy = findExpectedEntropy(j,i,test, pHit);
            cout<< "(" << j << "," << i << "): " << entropy<<endl;
        }
    }

    return 0;
}

