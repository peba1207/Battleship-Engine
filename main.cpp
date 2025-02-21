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
    //1
    test->setHit(1,0);
    test->setEmpty(1,0);

    //2
    test->setEmpty(6,0);

    //3
    test->setEmpty(5,1);

    //4
    test->setEmpty(5,4);

    //5
    test->setEmpty(2,4);

    //6
    test->setHit(7,6);
    test->setEmpty(7,6);

    //7
    test->setHit(5,6);
    test->setEmpty(5,6);

    //8
   test->setEmpty(6,6);

   //9
    test->setHit(7,1);
    test->setEmpty(7,1);

    //10
    test->setEmpty(4,6);

    //11
    test->markShip(1,0,2, test, true);

    //12
    test->setEmpty(1,5);

    //13
    test->setHit(2,6);
    test->setEmpty(2,6);

    //14
    test->setEmpty(1,6);

    //15
    test->setEmpty(3,2);

    //16
    test->setEmpty(4,2);

    //17
    test->setEmpty(4,0);
    test->setHit(4,0);

    //18
    test->setEmpty(0,5);
    test->setHit(0,5);

    //19
    test->setEmpty(0,7);

    //20
    test->setEmpty(4,1);

    //21
    test->markShip(2,6, 2, test,false);

    //22
    test->setEmpty(7,3);

    //23
    test->setEmpty(0,3);
    test->setHit(0,3);

    //24
    test->setEmpty(7,4);
    test->setHit(7,4);

    //25
    test->setEmpty(0,6);
    test->setHit(0,6);

    //26
    test->setEmpty(3,0);
    test->setHit(3,0);

    //27
    test->setEmpty(7,0);
    cout<<test->toString();
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

