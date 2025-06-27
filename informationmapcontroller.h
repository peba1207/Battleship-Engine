#ifndef INFORMATIONMAPCONTROLLER_H
#define INFORMATIONMAPCONTROLLER_H


#include <QObject>
#include "BoardState.h"
#include "BoardCalculations.h"
#include <string>
#include <QColor>
#include <QThread>
#include <QTimer>
#include <sstream>
#include <iostream>
#include <QDebug>

class InformationMapWorker : public QObject{
    Q_OBJECT
public:
    InformationMapWorker();
    double entropyDistribution[8][8];
public slots:
    void calculateMap(BoardState* state, double tileHeat[8][8]);
signals:
    void finishedCalculation();
private:
    double* tileHeat[8];
    QThread _thread;
};

class InformationMapController : public QObject
{
    Q_OBJECT
public:
    explicit InformationMapController(QObject *parent = nullptr, BoardState* state = nullptr);
    double tileHeat[8][8];
public slots:
    QColor tileColor(int row, int col);
    void updateMap();
    void getIntermediateCalculations();
    bool isBestMove(int row, int col);
    QString getExpectedInfoGain(int row, int col);
signals:
    void updatedMap();
    void startCalculation(BoardState* state, double tileHeat[8][8]);
private:
    void getMax();
    QTimer *timer;
    BoardState* state;
    InformationMapWorker workerThread;
    QThread _thread;
    double max = INFINITY;
};

#endif // INFORMATIONMAPCONTROLLER_H
