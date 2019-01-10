#include "enemy.h"
#include "game.h"
#include "island.h"
#include "player2.h"
#include "projectile.h"

#include <QCoreApplication>
#include <QDebug>
#include <QMessageBox>

#include <qmath.h>

extern game *gameVar;

player2::player2(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/player2vessel.png"));

    // Rotate around center of pixmap
    setTransformOriginPoint(11,30);

    // Initializing member variables
    m_angle = 0;
    m_dx = 0;
    m_dy = 0;
    m_reloadFlag = 1;

    QTimer *moveTimer = new (std::nothrow) QTimer(this);
    m_reloadTimer = new (std::nothrow) QTimer(this);

    if(moveTimer == nullptr || m_reloadTimer == nullptr)
    {
        qDebug() << "Failed to allocate player1 timer memory";
    }

    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    connect(m_reloadTimer, SIGNAL(timeout()),this, SLOT(reloadTime()));

    moveTimer->start(50);
}

player2::~player2()
{

}

void player2::setAngle(int angle)
{
    m_angle = angle;
}

int player2::getAngle()
{
    return m_angle;
}

void player2::setDx(double dx)
{
    m_dx = dx;
}

double player2::getDx()
{
    return m_dx;
}

void player2::setDy(double dy)
{
    m_dy = dy;
}

double player2::getDy()
{
    return m_dy;
}

void player2::setReloadFlag(bool reloaded)
{
    m_reloadFlag = reloaded;
}

bool player2::getReloadFlag()
{
    return m_reloadFlag;
}

// Player2 main move function
void player2::move()
{
    // Checking for collision between player2 and enemy
    // Not checking for collision between player2 and island as player2 follows same path as player1
    QList<QGraphicsItem*> collidingItemList = collidingItems();
    for(int i = 0, n = collidingItemList.size(); i < n; ++i)
    {
        enemy *enemyVar = dynamic_cast<enemy *>(collidingItemList[i]);

        // If enemy, delete enemy, reduce health points
        if(enemyVar)
        {
            gameVar->changeHealth(-3);

            scene()->removeItem(enemyVar);
            delete enemyVar;

            if(gameVar->getHealth() < 1 && gameVar->getMsgBoxFlag() == 0)
            {
                gameVar->setMsgBoxFlag(1);

                QMessageBox msgBox;
                msgBox.setText("Out of health points! Game over.");
                msgBox.exec();

                delete gameVar;
                QCoreApplication::quit();

                return;
            }
        }
    }

    setDx(gameVar->getPlayer1DelayedDx());
    setDy(gameVar->getPlayer1DelayedDy());
    setAngle(gameVar->getPlayer1DelayedAngle());

    setRotation(getAngle());
    setPos(x()+getDx(), y()+getDy());
}

void player2::reloadTime()
{
    setReloadFlag(1);
}

void player2::startReloadTimer()
{
    setReloadFlag(0);
    m_reloadTimer->start(2000);
}
