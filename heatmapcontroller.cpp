#include "heatmapcontroller.h"
#include "BoardCalculations.h"
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <QDebug>
using namespace std;
HeatmapController::HeatmapController(QObject *parent, BoardState* state)
    : QObject{parent}
{
    this->state = state;

    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            tileHeat[i][j] = 0;
        }
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HeatmapController::getIntermediateCalculations);
    timer->setSingleShot(false);

    connect(this,&HeatmapController::startCalculation, &workerThread, &HeatmapWorker::calculateMap);
    workerThread.moveToThread(&_thread);
    _thread.start();
    connect(&workerThread, &HeatmapWorker::finishedCalculation, this, [this](){
        timer->stop();
        qDebug() << "woah";
        emit updatedMap();
    });

    //connect(&_thread, &QThread::finished, this, &HeatmapController::updatedMap);

}

QColor HeatmapController::tileColor(int row, int col)
{
    int brightness = 255-tileHeat[row][col]*255;
    return QColor(brightness,brightness,255);
}

void HeatmapController::updateMap()
{
    timer->start(100);
    _thread.terminate();
    _thread.start();
    qDebug() << _thread.isRunning();

    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            tileHeat[i][j] = 0;
        }
    }

    emit updatedMap();
    emit startCalculation(state, tileHeat);
}

void HeatmapController::getIntermediateCalculations()
{
    unsigned long long shipCounts[8][8];
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            shipCounts[i][j] = workerThread.shipCounts[i][j];
        }
    }
    unsigned long long total = 0;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            total+=shipCounts[i][j];
        }
    }
    total = total/19;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            tileHeat[i][j] = (double)shipCounts[i][j]/total;
        }
    }
    emit updatedMap();
}



HeatmapWorker::HeatmapWorker()
{
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            shipCounts[i][j] = 0;
        }
    }
}

void HeatmapWorker::calculateMap(BoardState *state, double tileHeat[8][8])
{
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            shipCounts[i][j] = 0;
        }
    }

    unsigned long long int total = BoardCalculations::getAllBoards(state,shipCounts);
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            tileHeat[i][j] = (double)shipCounts[i][j]/total;
        }
    }

    emit finishedCalculation();
}

