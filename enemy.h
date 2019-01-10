#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPointF>

class enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enemy(QGraphicsItem *parent=0);
    ~enemy();

    void setAngle(int angle);
    int getAngle();

    void rotateToPoint(QPointF p);

    void setHealth(int input);
    void changeHealth(int input);
    int getHealth();

public slots:
    void moveFoward();

private:
    int m_angle;
    int m_health;

    QPointF m_destination;
};

#endif // ENEMY_H
