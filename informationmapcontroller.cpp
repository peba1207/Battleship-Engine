#include "informationmapcontroller.h"

InformationMapController::InformationMapController(QObject *parent, BoardState *state)
{
    this->state = state;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            tileHeat[i][j] = 0;
        }
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &InformationMapController::getIntermediateCalculations);
    timer->setSingleShot(false);

    connect(this,&InformationMapController::startCalculation, &workerThread, &InformationMapWorker::calculateMap);
    workerThread.moveToThread(&_thread);
    _thread.start();

    connect(&workerThread, &InformationMapWorker::finishedCalculation, this, [this](){
        timer->stop();
        qDebug() << "woah";
        getMax();
        emit updatedMap();
    });
}

QColor InformationMapController::tileColor(int row, int col)
{
    //int brightness = 255-tileHeat[row][col]*255;
    int red = 230-(230*tileHeat[row][col]/max);
    //int green = 230-(230*tileHeat[row][col]);
    int blue = 255-((255-102)*tileHeat[row][col]/max);
    return QColor(red,red,blue);

    return QColor(red,red,blue);
}

void InformationMapController::updateMap()
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

void InformationMapController::getIntermediateCalculations(){}

bool InformationMapController::isBestMove(int row, int col)
{
    return tileHeat[row][col]>=max-0.0001;
}
QString InformationMapController::getExpectedInfoGain(int row, int col)
{
    return QString::number(tileHeat[row][col],'f',3);
}


void InformationMapController::getMax()
{
    max = 0;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if(!state->revealed[i][j] && tileHeat[i][j]>max){
                max = tileHeat[i][j];
            }
        }
    }
    qDebug() << "max:" << max;

}

InformationMapWorker::InformationMapWorker()
{
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            entropyDistribution[i][j] = 0;
        }
    }
}

void InformationMapWorker::calculateMap(BoardState *state, double tileHeat[8][8])
{
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            entropyDistribution[i][j] = 0;
        }
    }
    BoardCalculations::getExpectedEntropy(state, entropyDistribution);

    /*unsigned long long total = 0;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            total += entropyDistribution[i][j];
        }
    }
    total = total/19;*/
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            tileHeat[i][j] = entropyDistribution[i][j];
        }
    }

    emit finishedCalculation();
}
