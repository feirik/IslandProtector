#ifndef GAME_H
#define GAME_H

#include "healthwidget.h"
#include "infowidget.h"
#include "island.h"
#include "player1.h"
#include "player2.h"
#include "scorewidget.h"

#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>
#include <QPointer>
#include <Qstring>

class game : public QGraphicsView
{
public:
    game();
    ~game();

    void mousePressEvent(QMouseEvent *event);

    void setHealth(int input);
    void changeHealth(int input);
    int getHealth();

    void setScore(long int input);
    void changeScore(long int input);
    long int getScore();

    void setMsgBoxFlag(bool input);
    bool getMsgBoxFlag();

    void removeInfo();

    double getPlayer1DelayedXPos();
    double getPlayer1DelayedYPos();
    double getPlayer1DelayedDx();
    double getPlayer1DelayedDy();
    int getPlayer1DelayedAngle();

private:
    QGraphicsScene* m_scene;

    QPointer<player1> m_player1;
    QPointer<player2> m_player2;

    QPointer<island> m_island;

    QPointer<healthWidget> m_healthWidget;
    QPointer<scoreWidget> m_scoreWidget;
    QPointer<infoWidget> m_infoWidget;

    int m_health;
    long int m_score;
    bool m_msgBoxFlag;
};

#endif // GAME_H
