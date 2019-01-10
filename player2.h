#ifndef PLAYER2_H
#define PLAYER2_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QList>
#include <QObject>
#include <QTimer>

class player2 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    player2(QGraphicsItem *parent = 0);
    ~player2();

    // Rotation angle in degrees
    void setAngle(int angle);
    int getAngle();

    void setDx(double dx);
    double getDx();

    void setDy(double dy);
    double getDy();

    void setReloadFlag(bool reloaded);
    bool getReloadFlag();

    void startReloadTimer();

public slots:
    void move();
    void reloadTime();

private:
    double m_angle;
    double m_dx;
    double m_dy;

    bool m_reloadFlag;

    QTimer* m_reloadTimer;
};

#endif // PLAYER2_H
