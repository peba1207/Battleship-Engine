//
// Created by peyto on 3/13/2025.
//

#ifndef BATTLESHIP_BOARDCALCULATIONS_H
#define BATTLESHIP_BOARDCALCULATIONS_H
#include <iostream>
#include "BoardState.h"

class BoardCalculations {
public:
    static void printDistribution(double distribution[SIZE][SIZE]);

    static void printDistribution(unsigned long long int (*distribution)[SIZE]);

    static unsigned long long int getAllBoards(BoardState* state, unsigned long long int shipCounts[SIZE][SIZE]);

    static void getExpectedEntropy(BoardState* state, double informationDistribution[SIZE][SIZE]);

private:

    static double findEntropy(unsigned long long int shipCounts[SIZE][SIZE], unsigned long long int total);

    static void getExpectedEntropyHelper(BoardState *state, unsigned long long shipCountsHit[SIZE][SIZE][SIZE][SIZE], int startX, int startY);

    static void getAllBoardsHelper(BoardState* state,  unsigned long long int shipCount[SIZE][SIZE], int startX, int startY);

    static void removeSunkenShips(BoardState* state);

    static int isSunkenShip(BoardState *state, int x, int y);
};

#endif //BATTLESHIP_BOARDCALCULATIONS_H
