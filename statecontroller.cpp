#include "statecontroller.h"
StateController::StateController(QObject *parent, BoardState* state)
    : QObject{parent}
{
    this->state = state;
}

void StateController::setEmpty(int row, int col)
{
    state->setRevealed(col, row);
    state->ships[row][col] = false;
    emit stateChanged();
}

void StateController::setHit(int row, int col)
{
    state->setHit(col,row);
    state->setRevealed(col,row);
    emit stateChanged();
}

void StateController::clearTile(int row, int col)
{
    state->revealed[row][col] = false;
    state->ships[row][col] = false;
    emit stateChanged();
}


