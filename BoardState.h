//
// Created by peyto on 2/18/2025.
//

#ifndef BATTLESHIP_BOARDSTATE_H
#define BATTLESHIP_BOARDSTATE_H
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;
const int SIZE = 8;
const int SHIPTILES = 19;
class BoardState {
public:
    bool revealed[SIZE][SIZE];
    bool ships[SIZE][SIZE];
    explicit BoardState(BoardState *pState);
    BoardState();
    unsigned long long int getAllBoards(unsigned long long int shipCounts[SIZE][SIZE]);
    void getAllBoardsHelper(const vector<int>& shipSizes, BoardState* state,  unsigned long long int shipCount[SIZE][SIZE], int startX, int startY);
    bool validSpot(int x, int y, int shipSize, bool vert);
    string toString();


    void setRevealed(int x, int y);
    void markShip(int x, int y, int size, BoardState *state, bool vert);

    void setHit(int x, int y);
};



#endif //BATTLESHIP_BOARDSTATE_H
