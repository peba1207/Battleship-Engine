#include <iostream>
#include "BoardState.h"
#include "BoardCalculations.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto *test = new BoardState();

    cout<< test->toString();
    unsigned long long int shipCounts[SIZE][SIZE];
    double expectedEntropy[SIZE][SIZE];

    unsigned long long int total = BoardCalculations::getAllBoards(test,shipCounts);
    cout << total << endl;
    BoardCalculations::printDistribution(shipCounts);

    delete test;
    return 0;
}

