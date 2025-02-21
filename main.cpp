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
    test->setHit(1,0);
    test->setEmpty(1,0);

    test->setEmpty(6,0);

    test->setEmpty(5,1);

    test->setEmpty(5,4);

    test->setEmpty(2,4);

    test->setHit(7,6);
    test->setEmpty(7,6);

    test->setHit(5,6);
    test->setEmpty(5,6);

   // test->setEmpty(6,6);

    unsigned long long int shipCounts[SIZE][SIZE];
    double expectedEntropy[SIZE][SIZE];
    unsigned long long int total = test->getAllBoards(shipCounts);

    double min = 1000;
    int minX = 0;
    int minY = 0;

    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE;j++){
            double pHit = (double)shipCounts[i][j]/(double)total;
            double entropy = findExpectedEntropy(j,i,test, pHit);
            cout<< "(" << j << "," << i << "): " << entropy<<endl;
            expectedEntropy[i][j] = entropy;
            if(entropy<min){min = entropy; minX = j; minY = i;}
        }
    }

    for (int i = 0; i<SIZE; i++){
        for (int j = 0; j<SIZE; j++){
            cout<< expectedEntropy[i][j];
            if(j!=SIZE-1){cout<<", ";}
        }
        cout << endl;
    }
    cout << "Min: " << min << " at (" << minX << ", " << minY << ")";
    delete test;
    return 0;
}

