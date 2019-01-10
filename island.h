#ifndef ISLAND_H
#define ISLAND_H

#include <QGraphicsPixmapItem>
#include <QObject>

class island : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    island();
    ~island();

    void setEnemyCount(int input);
    void changeEnemyCount(int input);
    int getEnemyCount();

public slots:
    void spawnEnemy();

private:
    int m_enemyCount;
    QTimer* m_spawnTimer;
};

#endif // ISLAND_H
