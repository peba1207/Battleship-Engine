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
class BoardState {
    bool empty[SIZE][SIZE]{};
    bool ships[SIZE][SIZE]{};

public:
    explicit BoardState(BoardState *pState);
    BoardState();
    unsigned long int getAllBoards();
    void getAllBoardsHelper(const vector<int>& shipSizes, BoardState* state,  long int shipCount[SIZE][SIZE], int startX, int startY);
    bool validSpot(int x, int y, int shipSize, bool vert);
    string toString();


    void setEmpty(int x, int y);
    void markShip(int x, int y, int size, BoardState *state, bool vert);

};



#endif //BATTLESHIP_BOARDSTATE_H
