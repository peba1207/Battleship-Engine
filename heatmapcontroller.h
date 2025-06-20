#ifndef HEATMAPCONTROLLER_H
#define HEATMAPCONTROLLER_H

#include <QObject>
#include "BoardState.h"
#include <string>
#include <QColor>
class HeatmapController : public QObject
{
    Q_OBJECT
public:
    explicit HeatmapController(QObject *parent = nullptr, BoardState* state = nullptr);

public slots:
    QColor tileColor(int row, int col);
    void updateMap();
signals:
    void updatedMap();
private:
    BoardState* state;
    double tileHeat[8][8];
};

#endif // HEATMAPCONTROLLER_H
