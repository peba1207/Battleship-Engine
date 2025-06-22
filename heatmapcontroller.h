#ifndef HEATMAPCONTROLLER_H
#define HEATMAPCONTROLLER_H

#include <QObject>
#include "BoardState.h"
#include <string>
#include <QColor>
#include <QThread>
#include <QTimer>

class HeatmapWorker : public QObject{
    Q_OBJECT
public:
    HeatmapWorker();
    unsigned long long int shipCounts[8][8];
public slots:
    void calculateMap(BoardState* state, double tileHeat[8][8]);
signals:
    void finishedCalculation();
private:
    double* tileHeat[8];
    QThread _thread;
};

class HeatmapController : public QObject
{
    Q_OBJECT
public:
    explicit HeatmapController(QObject *parent = nullptr, BoardState* state = nullptr);
    double tileHeat[8][8];
public slots:
    QColor tileColor(int row, int col);
    void updateMap();
    void getIntermediateCalculations();
signals:
    void updatedMap();
    void startCalculation(BoardState* state, double tileHeat[8][8]);
private:
    QTimer *timer;
    BoardState* state;
    HeatmapWorker workerThread;
    QThread _thread;
};

#endif // HEATMAPCONTROLLER_H
