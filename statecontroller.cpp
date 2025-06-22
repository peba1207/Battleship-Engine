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

void StateController::sinkShip(int row, int col)
{
    int shipSize = 1;
    state->setHit(col,row);
    int minRow = row;
    int minCol = col;
    for(int i = row + 1; i < 8 && state->ships[i][col]; i++){
        shipSize++;
    }
    for(int i = row - 1; i >= 0 && state->ships[i][col]; i--){
        minRow = i;
        shipSize++;
    }
    if(shipSize > 1){
        state->markShip(col,minRow, shipSize, state, true);
        qDebug() << col << " " << minRow;
        emit stateChanged();
        return;
    }
    for(int i = col + 1; i < 8 && state->ships[row][i]; i++){
        shipSize++;
    }
    for(int i = col - 1; i >= 0 && state->ships[row][i]; i--){
        minCol = i;
        shipSize++;
    }
    state->markShip(minCol,row, shipSize, state, false);

    emit stateChanged();
}



