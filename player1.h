#ifndef PLAYER1_H
#define PLAYER1_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QObject>
#include <QTimer>

class player1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    player1(QGraphicsItem *parent = 0);
    ~player1();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void playerAction();

    // Rotation angle in degrees
    void setAngle(int angle);
    int getAngle();

    void setDx(double dx);
    double getDx();

    void setDy(double dy);
    double getDy();

    void setReloadFlag(bool reloaded);
    bool getReloadFlag();

    double getDelayedXPos();
    double getDelayedYPos();
    double getDelayedDx();
    double getDelayedDy();
    int getDelayedAngle();

public slots:
    void move();
    void actionLoop();
    void reloadTime();

private:
    double m_angle;
    double m_dx;
    double m_dy;

    bool m_reloadFlag;

    QList<bool> m_keyPressArray;
    QTimer* m_reloadTimer;

    void accelerate();
    void decellerate();
    void rotateCCW(int degrees);
    void rotateCW(int degrees);
    void fireCannons();

    QList<double> m_xPosList;
    QList<double> m_yPosList;
    QList<double> m_dxList;
    QList<double> m_dyList;
    QList<int> m_angleList;
};

#endif // PLAYER1_H
