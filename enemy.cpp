#include "enemy.h"
#include "game.h"

#include <QCoreApplication>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>
#include <QTimer>

#include <qmath.h>
#include <stdlib.h>

extern game *gameVar;

enemy::enemy(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/enemyMoving.png"));

    // Spawning enemy from one of the four boarders, rand() seed initialized in island class constructor
    int randomBoarder = rand()%4;

    // Left boarder
    if(randomBoarder == 0)
    {
        // rand()%70 * 10 to get a better random number distribution,
        // -100 to spawn enemy outside of screen as pixmap rotation twitches during spawn
        int randomY = (rand()%70 * 10) - 100;
        setPos(-100, randomY);
    }

    // Right boarder
    else if(randomBoarder == 1)
    {
        int randomY = (rand()%70 * 10) - 100;
        setPos(900, randomY);
    }

    // Top boarder
    else if(randomBoarder == 2)
    {
        int randomX = (rand()%90 * 10) - 100;
        setPos(randomX, -100);
    }

    // Bottom boarder
    else if(randomBoarder == 3)
    {
        int randomX = (rand()%90 * 10) - 100;
        setPos(randomX, 700);
    }

    // Rotate around center of pixmap
    setTransformOriginPoint(11,30);

    // Set island as destination for enemy direction
    m_destination = QPointF(400,300);

    // Initialize health points for enemy
    m_health = 3;

    QTimer *timerVar = new (std::nothrow) QTimer(this);

    if(timerVar == nullptr)
    {
        qDebug() << "Failed to allocate enemy timerVar memory";
    }

    connect(timerVar,SIGNAL(timeout()),this,SLOT(moveFoward()));
    timerVar->start(50);
}

enemy::~enemy()
{

}

void enemy::setAngle(int angle)
{
    m_angle = angle;
}

int enemy::getAngle()
{
    return m_angle;
}

// Takes a Qpoint float input, creates a line between current pixmap position and point
// Updates the enemy object angle based on line angle relative to coordinate system
void enemy::rotateToPoint(QPointF p)
{
    QLineF line(pos(),p);
    setAngle(-1 * line.angle());
}

void enemy::setHealth(int input)
{
    m_health = input;
}

void enemy::changeHealth(int input)
{
    m_health = m_health + input;
}

int enemy::getHealth()
{
    return m_health;
}

// Main move function for enemy
void enemy::moveFoward()
{
    // Collision check between enemy and island
    QList<QGraphicsItem*> collidingItemList = collidingItems();
    for(int i = 0, n = collidingItemList.size(); i < n; ++i)
    {
        // Checking if colliding item is an island class
        island *islandVar = dynamic_cast<island *>(collidingItemList[i]);

        // If in contact with island, delete enemy, decrement health points
        if(islandVar)
        {
            scene()->removeItem(this);
            gameVar->changeHealth(-3);

            delete this;

            // Quit application if health is below 1, flag check to avoid duplicate message boxes
            if(gameVar->getHealth() < 1 && gameVar->getMsgBoxFlag() == 0)
            {
                gameVar->setMsgBoxFlag(1);

                QMessageBox msgBox;
                msgBox.setText("Out of health points! Game over.");
                msgBox.exec();

                delete gameVar;
                QCoreApplication::quit();
            }
            return;
        }
    }

    // Set stepsize (pixmap velocity is a function of timer->start(value) and STEPSIZE)
    int STEPSIZE = 2;

    double theta = getAngle();

    // Update travel direction for pixmap
    rotateToPoint(m_destination);

    // Update orientation for pixmap, +90 degrees to account for pixmap coordinate system
    setRotation(getAngle()+90);

    // Update velocity magnitudes and direction
    double dx = STEPSIZE * qCos(qDegreesToRadians(theta));
    double dy = STEPSIZE * qSin(qDegreesToRadians(theta));

    // Update position
    setPos(x()+dx, y()+dy);
}
