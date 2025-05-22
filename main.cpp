#include <iostream>
#include "BoardState.h"
#include "BoardCalculations.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto *test = new BoardState();
    test->setRevealed(1,0);
    test->setRevealed(0,1);
    test->setRevealed(2,1);

    test->setRevealed(1,2);
    test->setHit(1,2);

    test->setRevealed(0,6);
    test->setHit(0,6);

    test->setRevealed(2,6);
    test->setHit(2,6);

    test->markShip(0,6,3,test,false);

    test->setRevealed(1,4);
    test->setHit(1,4);

    test->setRevealed(1,3);

    test->setRevealed(0,4);

    test->markShip(1,4,2,test,false);

    test->setRevealed(6,7);

    test->setRevealed(7,6);
    test->setHit(7,6);

    test->setRevealed(5,6);

    test->setRevealed(4,7);

    test->setRevealed(4,5);
    test->setHit(4,5);

    test->setRevealed(7,5);

    test->setRevealed(7,2);

    test->setRevealed(2,2);
    test->setHit(2,2);

    test->setRevealed(0,2);


    test->markShip(1,2, 4, test,false);

    test->markShip(4,4,3,test,true);

    test->setRevealed(5,0);

    test->setRevealed(3,0);
    test->setHit(3,0);

    test->setRevealed(2,0);

    test->setRevealed(4,0);
    test->setHit(4,0);

    test->setRevealed(6,2);
    test->setHit(6,2);

    cout<< test->toString();
    unsigned long long int shipCounts[SIZE][SIZE];
    double expectedEntropy[SIZE][SIZE];

    unsigned long long int total = test->getAllBoards(shipCounts);
    cout << total << endl;
    //BoardCalculations::printDistribution(shipCounts);


    BoardCalculations::findEntropyOfEachTile(test,expectedEntropy);

    //get minimum
    double min = 1000;
    int minX = 0;
    int minY = 0;
    for (int i = 0; i<SIZE; i++){
        for (int j = 0; j<SIZE; j++){
            double entropy = expectedEntropy[i][j];
            if((entropy<min && entropy >0) || entropy == -1){
                min = expectedEntropy[i][j];
                minX = j;
                minY = i;
            }
        }
    }

    BoardCalculations::printDistribution(expectedEntropy);
    //BoardCalculations::printDistribution(shipCounts);

    cout << "Min: " << min << " at (" << minX << ", " << minY << ")";
    delete test;
    return 0;
}

