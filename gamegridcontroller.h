#ifndef GAMEGRIDCONTROLLER_H
#define GAMEGRIDCONTROLLER_H

#include <QObject>

class GameGridController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int selectedCol READ selectedCol WRITE setSelectedCol NOTIFY colChanged)
    Q_PROPERTY(int selectedRow READ selectedRow WRITE setSelectedRow NOTIFY rowChanged)

public:
    explicit GameGridController(QObject *parent = nullptr);

    int selectedCol() const;
    void setSelectedCol(int newSelectedCol);

    int selectedRow() const;
    void setSelectedRow(int newSelectedRow);

public slots:

signals:
    void colChanged();
    void rowChanged();

private:
    int m_selectedCol = 0;
    int m_selectedRow = 0;
};

#endif // GAMEGRIDCONTROLLER_H
