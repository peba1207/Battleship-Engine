#include "heatmapcontroller.h"
#include "BoardCalculations.h"
#include <sstream>

HeatmapController::HeatmapController(QObject *parent, BoardState* state)
    : QObject{parent}
{
    this->state = state;

    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            tileHeat[i][j] = 0;
        }
    }
}

QColor HeatmapController::tileColor(int row, int col)
{
    int brightness = 255-tileHeat[row][col]*255;
    return QColor(brightness,brightness,255);
}

void HeatmapController::updateMap()
{
    unsigned long long int shipCounts[8][8];
    unsigned long long int total = BoardCalculations::getAllBoards(state,shipCounts);
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            tileHeat[i][j] = (double)shipCounts[i][j]/total;
        }
    }
    emit updatedMap();
}

