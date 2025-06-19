#include "gamegridcontroller.h"

GameGridController::GameGridController(QObject *parent, BoardState* state)
    : QObject{parent}
{
    this->state = state;
}

int GameGridController::selectedCol() const
{
    return m_selectedCol;
}

void GameGridController::setSelectedCol(int newSelectedCol)
{
    if (m_selectedCol == newSelectedCol)
        return;
    m_selectedCol = newSelectedCol;
    emit colChanged();
}

int GameGridController::selectedRow() const
{
    return m_selectedRow;
}

void GameGridController::setSelectedRow(int newSelectedRow)
{
    if (m_selectedRow == newSelectedRow)
        return;
    m_selectedRow = newSelectedRow;
    emit rowChanged();
    emit stateChanged();
}

bool GameGridController::isHit(int row, int column)
{
    return state->ships[row][column];
}

bool GameGridController::isMiss(int row, int column)
{
    return state->revealed[row][column] && !state->ships[row][column];
}
