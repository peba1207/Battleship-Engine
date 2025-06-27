#include "heatmapcontroller.h"
#include "BoardCalculations.h"

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
        getMax();
        emit updatedMap();
    });

    //connect(&_thread, &QThread::finished, this, &HeatmapController::updatedMap);

}

QColor HeatmapController::tileColor(int row, int col)
{
    //int brightness = 255-tileHeat[row][col]*255;
    int red = 230-(230*tileHeat[row][col]);
    //int green = 230-(230*tileHeat[row][col]);
    int blue = 255-((255-102)*tileHeat[row][col]);
    return QColor(red,red,blue);
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

bool HeatmapController::isBestMove(int row, int col)
{
    return tileHeat[row][col]>=max-0.0001;
}

QString HeatmapController::getProb(int row, int col)
{
    return QString::number(tileHeat[row][col]*100,'f',1) + "%";
}

void HeatmapController::getMax()
{
    max = 0;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if(!state->revealed[i][j] && tileHeat[i][j]>max){
                max = tileHeat[i][j];
            }
        }
    }
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

