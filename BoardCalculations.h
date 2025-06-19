//
// Created by peyto on 3/13/2025.
//

#ifndef BATTLESHIP_BOARDCALCULATIONS_H
#define BATTLESHIP_BOARDCALCULATIONS_H
#include <iostream>
#include "BoardState.h"

class BoardCalculations {
public:
    static double findEntropy(unsigned long long int shipCounts[SIZE][SIZE], unsigned long long int total);

    static double findExpectedEntropy(int x, int y, BoardState *state, double pHit);

    static double findEntropyOfMiss(int x, int y, BoardState *state);

    static double findEntropyOfEachTile(BoardState *state, double entropyDistribution[SIZE][SIZE]);

    static void printDistribution(double distribution[SIZE][SIZE]);

    static void printDistribution(unsigned long long int (*distribution)[SIZE]);

    static unsigned long long int getAllBoards(BoardState* state, unsigned long long int shipCounts[SIZE][SIZE]);
private:
    static void getAllBoardsHelper(BoardState* state,  unsigned long long int shipCount[SIZE][SIZE], int startX, int startY);
};

#endif //BATTLESHIP_BOARDCALCULATIONS_H
