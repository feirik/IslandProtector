#include "enemy.h"
#include "game.h"
#include "island.h"
#include "player1.h"
#include "projectile.h"

#include <QCoreApplication>
#include <QDebug>
#include <QMessageBox>

#include <qmath.h>

extern game *gameVar;

player1::player1(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/vessel.png"));

    // Rotate around center of pixmap
    setTransformOriginPoint(11,30);

    // Initializing member variables
    m_angle = 0;
    m_dx = 0;
    m_dy = 0;
    m_reloadFlag = 1;

    // Initializing keyPressArray to false for all inputs
    for(int i = 0; i < 5; ++i)
    {
        m_keyPressArray.append(0);
    }

    // Initializing player1 move parameters, 40 entries for 2 sec delay
    for(int i = 0; i < 40; ++i)
    {
        m_xPosList.append(0);
        m_yPosList.append(0);
        m_dxList.append(0);
        m_dyList.append(0);
        m_angleList.append(0);
    }

    QTimer *moveTimer = new (std::nothrow) QTimer(this);
    QTimer *actionTimer = new (std::nothrow) QTimer(this);
    m_reloadTimer = new (std::nothrow) QTimer(this);

    if(moveTimer == nullptr || actionTimer == nullptr || m_reloadTimer == nullptr)
    {
        qDebug() << "Failed to allocate player1 timer memory";
    }

    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    connect(actionTimer, SIGNAL(timeout()),this, SLOT(actionLoop()));
    connect(m_reloadTimer, SIGNAL(timeout()),this, SLOT(reloadTime()));

    actionTimer->start(50);
    moveTimer->start(50);
}

player1::~player1()
{

}

// Update keyPressArray based on what buttons are pressed
void player1::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        m_keyPressArray.replace(0,1);
    }
    if(event->key() == Qt::Key_Right)
    {
        m_keyPressArray.replace(1,1);
    }
    // Accellerate in foward direction of pixmap
    if(event->key() == Qt::Key_Up)
    {
        m_keyPressArray.replace(2,1);
    }
    // Decellerate
    if(event->key() == Qt::Key_Down)
    {
        m_keyPressArray.replace(3,1);
    }
    // Fire cannons
    if(event->key() == Qt::Key_Space)
    {
        m_keyPressArray.replace(4,1);
    }
}

// Update keyPressArray based on what buttons are released
void player1::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        m_keyPressArray.replace(0,0);
    }
    if(event->key() == Qt::Key_Right)
    {
        m_keyPressArray.replace(1,0);
    }
    if(event->key() == Qt::Key_Up)
    {
        m_keyPressArray.replace(2,0);
    }
    if(event->key() == Qt::Key_Down)
    {
        m_keyPressArray.replace(3,0);
    }
    if(event->key() == Qt::Key_Space)
    {
        m_keyPressArray.replace(4,0);
    }
}

// Update player1 direction, acceleration and cannon firing based on combinations in keyPressArray
void player1::playerAction()
{
    // Degrees of rotation per left/right key input
    double TURN_SPEED = 10;

    if(m_keyPressArray.at(0) == 1 && m_keyPressArray.at(2) == 1 && m_keyPressArray.at(4) == 1)
    {
        fireCannons();
        rotateCCW(TURN_SPEED);
        accelerate();
        return;
    }

    if(m_keyPressArray.at(1) == 1 && m_keyPressArray.at(2) == 1 && m_keyPressArray.at(4) == 1)
    {
        fireCannons();
        rotateCW(TURN_SPEED);
        accelerate();
        return;
    }

    if(m_keyPressArray.at(0) == 1 && m_keyPressArray.at(3) == 1 && m_keyPressArray.at(4) == 1)
    {
        fireCannons();
        rotateCCW(TURN_SPEED);
        decellerate();
        return;
    }

    if(m_keyPressArray.at(1) == 1 && m_keyPressArray.at(3) == 1 && m_keyPressArray.at(4) == 1)
    {
        fireCannons();
        rotateCW(TURN_SPEED);
        decellerate();
        return;
    }

    if(m_keyPressArray.at(0) == 1 && m_keyPressArray.at(4) == 1)
    {
        fireCannons();
        rotateCCW(TURN_SPEED);
        return;
    }

    if(m_keyPressArray.at(1) == 1 && m_keyPressArray.at(4) == 1)
    {
        fireCannons();
        rotateCW(TURN_SPEED);
        return;
    }

    if(m_keyPressArray.at(2) == 1 && m_keyPressArray.at(4) == 1)
    {
        fireCannons();
        accelerate();
        return;
    }

    if(m_keyPressArray.at(3) == 1 && m_keyPressArray.at(4) == 1)
    {
        fireCannons();
        decellerate();
        return;
    }

    if(m_keyPressArray.at(0) == 1 && m_keyPressArray.at(2) == 1)
    {
        rotateCCW(TURN_SPEED);
        accelerate();
        return;
    }

    if(m_keyPressArray.at(1) == 1 && m_keyPressArray.at(2) == 1)
    {
        rotateCW(TURN_SPEED);
        accelerate();
        return;
    }

    if(m_keyPressArray.at(0) == 1 && m_keyPressArray.at(3) == 1)
    {
        rotateCCW(TURN_SPEED);
        decellerate();
        return;
    }

    if(m_keyPressArray.at(1) == 1 && m_keyPressArray.at(3) == 1)
    {
        rotateCW(TURN_SPEED);
        decellerate();
        return;
    }

    if(m_keyPressArray.at(0) == 1)
    {
        rotateCCW(TURN_SPEED);
        return;
    }

    if(m_keyPressArray.at(1) == 1)
    {
        rotateCW(TURN_SPEED);
        return;
    }

    if(m_keyPressArray.at(2) == 1)
    {
        accelerate();
        return;
    }

    if(m_keyPressArray.at(3) == 1)
    {
        decellerate();
        return;
    }

    if(m_keyPressArray.at(4) == 1)
    {
        fireCannons();
        return;
    }
}

void player1::setAngle(int angle)
{
    m_angle = angle;
}

int player1::getAngle()
{
    return m_angle;
}

void player1::setDx(double dx)
{
    m_dx = dx;
}

double player1::getDx()
{
    return m_dx;
}

void player1::setDy(double dy)
{
    m_dy = dy;
}

double player1::getDy()
{
    return m_dy;
}

void player1::setReloadFlag(bool reloaded)
{
    m_reloadFlag = reloaded;
}

bool player1::getReloadFlag()
{
    return m_reloadFlag;
}

// Returning the lists at position 39 equals a 2 second delay of player1 position, speed and angle
double player1::getDelayedXPos()
{
    return m_xPosList.at(39);
}

double player1::getDelayedYPos()
{
    return m_yPosList.at(39);
}

double player1::getDelayedDx()
{
    return m_dxList.at(39);
}

double player1::getDelayedDy()
{
    return m_dyList.at(39);
}

int player1::getDelayedAngle()
{
    return m_angleList.at(39);
}

// Main move function for player1
void player1::move()
{
    // Checking for collision between player1 and island or enemy
    QList<QGraphicsItem*> collidingItemList = collidingItems();
    for(int i = 0, n = collidingItemList.size(); i < n; ++i)
    {
        // Checking if colliding item is an island class
        island *islandVar = dynamic_cast<island *>(collidingItemList[i]);

        // If island, exit game
        if(islandVar)
        {
            if(gameVar->getMsgBoxFlag() == 0)
            {
                gameVar->setMsgBoxFlag(1);
                // Set health points to 0, changeHealth called to update widget
                gameVar->setHealth(0);
                gameVar->changeHealth(0);

                QMessageBox msgBox;
                msgBox.setText("You beached your ship! Game over.");
                msgBox.exec();

                delete gameVar;
                QCoreApplication::quit();
            }
            return;
        }

        enemy *enemyVar = dynamic_cast<enemy *>(collidingItemList[i]);

        // If enemy, delete enemy, reduce health points
        if(enemyVar)
        {
            gameVar->changeHealth(-3);

            scene()->removeItem(enemyVar);
            delete enemyVar;

            // If health is below 1, exit game
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

    // Push back player1 if at the bounds of scene
    if(x()<0)
    {
        setDx(0.5);
    }
    if(x()>scene()->width()-20)
    {
        setDx(-0.5);
    }

    if(y()<-20)
    {
        setDy(0.5);
    }

    if(y()>scene()->height()-30)
    {
        setDy(-0.5);
    }

    // Logging historical position, speed and angle of player1 for the last 2 seconds
    // Logged x and y position is currently not in use, but could be used for enabling/disabling player2 while game is running
    m_xPosList.push_front(x());
    m_yPosList.push_front(y());
    m_dxList.push_front(getDx());
    m_dyList.push_front(getDy());
    m_angleList.push_front(getAngle());

    // Popping off oldest entry in lists, lists are kept at size of 40 entries
    m_xPosList.pop_back();
    m_yPosList.pop_back();
    m_dxList.pop_back();
    m_dyList.pop_back();
    m_angleList.pop_back();

    setPixmap(QPixmap(":/images/vessel.png"));

    // Update player1 position
    setPos(x()+getDx(), y()+getDy());
}

// Connected to loop timer to get user input in set intervals
void player1::actionLoop()
{
    playerAction();
}

// Connected to reload timer to set reload flag, allowing player1 to shoot
void player1::reloadTime()
{
    m_reloadFlag = 1;
}

// Accelerate player1 in the direction player1 pixmap is facing
void player1::accelerate()
{
    double ACCELERATION_STEP = 0.3;

    // Show different pixmap to indicate acceleration
    setPixmap(QPixmap(":/images/vesselMoving.png"));

    // Converting of pixmap rotation to 0 degrees starting at in x-direction for scene
    double theta = getAngle()+90;

    // Converting m_dy and m_dx directions to scene coordinate system
    m_dx += -1 * ACCELERATION_STEP * qCos(qDegreesToRadians(theta));
    m_dy += -1 * ACCELERATION_STEP * qSin(qDegreesToRadians(theta));
}

// Decrease speed regardless of direction
void player1::decellerate()
{
    setDx(getDx()*0.95);
    setDy(getDy()*0.95);
}

// Rotates pixmap an integer degrees in the counter clockwise direction
void player1::rotateCCW(int degrees)
{
    setAngle(getAngle()%360 - degrees);
    setRotation(getAngle());
}

// Rotates pixmap an integer degrees in the clockwise direction
void player1::rotateCW(int degrees)
{
    setAngle(getAngle()%360 + degrees);
    setRotation(getAngle());
}

// Fires three cannon balls relative to player ship location
void player1::fireCannons()
{
    if(m_reloadFlag == 1)
    {
        // Freed when projectile collides with enemy, island or bounds of scene
        projectile *projectileVar = new (std::nothrow) projectile();
        projectile *projectileVar2 = new (std::nothrow) projectile();
        projectile *projectileVar3 = new (std::nothrow) projectile();

        if(projectileVar == nullptr || projectileVar2 == nullptr || projectileVar3 == nullptr)
        {
            qDebug() << "Failed to allocate player1 projectiles memory";
        }

        projectileVar->setPos(x()+20,y()+10);
        projectileVar2->setPos(x()+20,y()+25);
        projectileVar3->setPos(x()+20,y()+40);

        projectileVar->setRotation(getAngle());
        projectileVar2->setRotation(getAngle());
        projectileVar3->setRotation(getAngle());

        gameVar->scene()->addItem(projectileVar);
        gameVar->scene()->addItem(projectileVar2);
        gameVar->scene()->addItem(projectileVar3);

        // Reduce score equal to damage potential of projectiles
        gameVar->changeScore(-3);

        // Start reload timer after cannonballs are fired
        m_reloadTimer->start(500);
        m_reloadFlag = 0;
    }
}
