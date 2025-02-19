//
// Created by peyto on 2/18/2025.
//

#ifndef BATTLESHIP_BOARDSTATE_H
#define BATTLESHIP_BOARDSTATE_H
#include <vector>
#include <string>
#include <iostream>
#include <random>

using namespace std;
const int SIZE = 8;
class BoardState {
    bool empty[SIZE][SIZE]{};
    bool ships[SIZE][SIZE]{};

public:
    explicit BoardState(BoardState *pState);
    BoardState();
    vector<BoardState*>* getAllBoards();
    vector<BoardState*>* getAllBoardsHelper(const vector<int>& shipSizes, BoardState* state);
    bool validSpot(int x, int y, int shipSize, bool vert);
    string toString();



    void markShip(int x, int y, int size, BoardState *state, bool vert);
};



#endif //BATTLESHIP_BOARDSTATE_H
