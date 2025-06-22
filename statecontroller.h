#ifndef STATECONTROLLER_H
#define STATECONTROLLER_H

#include <QObject>
#include "BoardState.h"
#include <QDebug>
class StateController : public QObject
{
    Q_OBJECT
public:
    explicit StateController(QObject *parent = nullptr, BoardState* state = nullptr);
public slots:
    void setEmpty(int row, int col);
    void setHit(int row, int col);
    void clearTile(int row, int col);
    void sinkShip(int row, int col);
signals:
    void stateChanged();
private:
    BoardState* state;
};

#endif // STATECONTROLLER_H
