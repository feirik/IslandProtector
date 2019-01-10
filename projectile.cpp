#include "enemy.h"
#include "game.h"
#include "island.h"
#include "projectile.h"

#include <QCoreApplication>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QMessageBox>
#include <QPixmap>
#include <QTimer>

#include <qmath.h>

extern game *gameVar;

projectile::projectile(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/cannonball.png"));

    // Default projectile speed
    m_stepSize = 30;

    // Default damage
    m_damage = 1;

    QTimer *moveTimer = new (std::nothrow) QTimer(this);

    if(moveTimer == nullptr)
    {
        qDebug() << "Failed to allocate projectile moveTimer memory";
    }

    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));

    // Set origo in center of pixmap
    setTransformOriginPoint(4,4);

    moveTimer->start(50);
}

projectile::~projectile()
{

}

void projectile::setStepSize(int input)
{
    m_stepSize = input;
}

int projectile::getStepSize()
{
    return m_stepSize;
}

void projectile::setDamage(int input)
{
    m_damage = input;
}

int projectile::getDamage()
{
    return m_damage;
}

void projectile::updatePixmap(QString directory)
{
    setPixmap(QPixmap(directory));
}

// Main move function for projectile
void projectile::move()
{
    // Collission check between projectile and island or enemy
    QList<QGraphicsItem*> collidingItemList = collidingItems();
    for(int i = 0, n = collidingItemList.size(); i < n; ++i)
    {
        // Checking if colliding item is an island class
        island *islandVar = dynamic_cast<island *>(collidingItemList[i]);

        // If island, delete bullet, decrement health
        if(islandVar)
        {
            scene()->removeItem(this);
            gameVar->changeHealth(-1 * getDamage());
            delete this;

            // Check if health is below 1 and flag check to avoid duplicate message boxes
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

        // Checking if colliding item is an enemy class
        enemy *enemyVar = dynamic_cast<enemy *>(collidingItemList[i]);

        // If enemy, delete bullet, decrement health of enemy, destroy enemy if health is below 1
        if(enemyVar)
        {
            enemyVar->changeHealth(-1 * getDamage());

            // Delete both enemy and projectile if health below 1
            if(enemyVar->getHealth() < 1)
            {
                // Code sequence below is imporant, otherwise application crashes
                scene()->removeItem(enemyVar);
                scene()->removeItem(this);

                // Update score
                gameVar->changeScore(10);

                delete enemyVar;
                delete this;
                return;
            }
            // Else delete just the projectile
            else
            {
                scene()->removeItem(this);
                delete this;

                return;
            }
        }
    }

    // Delete projectile at end of bounds in x-direction
    if(x() < 0 || x() > scene()->width())
    {
        scene()->removeItem(this);
        delete this;
        return;
    }

    // Delete projectile at end of bounds in y-direction, adjusted +-75 so player can fire all three projectiles at edge of bounds
    if(y() < -75 || y() > scene()->height() + 75)
    {
        scene()->removeItem(this);
        delete this;
        return;
    }

    int STEPSIZE = getStepSize();

    double theta = rotation();

    double dx = STEPSIZE * qCos(qDegreesToRadians(theta));
    double dy = STEPSIZE * qSin(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);
}
