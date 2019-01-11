#include "game.h"
#include "healthwidget.h"
#include "projectile.h"
#include "scorewidget.h"

#include <QDebug>
#include <QPointF>
#include <QTimer>

game::game()
{
    // Freed using Qt's parent - child relationship
    m_scene = new (std::nothrow) QGraphicsScene(this);

    if(m_scene == nullptr)
    {
        qDebug() << "Failed to allocate m_scene memory";
    }

    // Setting resolution and coordinate system
    m_scene->setSceneRect(0,0,800,600);

    // Initializing health points for player
    m_health = 10;

    // Initializing score points for player
    m_score = 0;

    m_msgBoxFlag = 0;

    setScene(m_scene);

    // Lock scene
    setFixedSize(800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_island = new (std::nothrow) island;

    if(m_island == nullptr)
    {
        qDebug() << "Failed to allocate m_island memory";
    }

    // Initialize island to center of map
    m_island->setPos(350,250);
    m_scene->addItem(m_island);

    // Needed for mouse events not to change focus during mouse presses
    m_scene->setStickyFocus(1);

    m_player1 = new (std::nothrow) player1;
    m_player2 = new (std::nothrow) player2;

    if(m_player1 == nullptr || m_player2 == nullptr)
    {
        qDebug() << "Failed to allocate m_player1/2 memory";
    }

    // Initializing players the same location, design choice to make player2 follow exact player1 path
    m_player1->setPos(400,400);
    m_player2->setPos(400,400);
    m_scene->addItem(m_player1);
    m_scene->addItem(m_player2);

    // Set focus for keyEvents for player1
    m_player1->setFlag(QGraphicsItem::ItemIsFocusable);
    m_player1->setFocus();

    m_healthWidget = new (std::nothrow) healthWidget;
    m_scoreWidget = new (std::nothrow) scoreWidget;
    m_infoWidget = new (std::nothrow) infoWidget;

    if(m_healthWidget == nullptr || m_scoreWidget == nullptr || m_infoWidget == nullptr)
    {
        qDebug() << "Failed to allocate health/score/info widget memory";
    }

    m_scene->addItem(m_healthWidget);
    m_scene->addItem(m_scoreWidget);
    m_scene->addItem(m_infoWidget);

    // Initialize widget positions, health widget is at default 0,0
    m_scoreWidget->setPos(600,0);
    m_infoWidget->setPos(300,30);

    m_healthWidget->updateWidget(getHealth());
    m_scoreWidget->updateWidget(getScore());
}

game::~game()
{

}

// Mouse press event for firing player2's cannonball towards location of mouse press
void game::mousePressEvent(QMouseEvent *event)
{
    // Player2 needs to be reloaded to fire
    if(m_player2->getReloadFlag() == 1)
    {
        m_player2->startReloadTimer();

        // Freed when projectile collides with enemy, island or bounds of scene
        projectile *projectileClickVar = new (std::nothrow) projectile();

        if(projectileClickVar == nullptr)
        {
            qDebug() << "Failed to allocate projectile memory";
        }

        // Update pixmap to big cannonball
        projectileClickVar->updatePixmap(":/images/cannonball_big.png");

        projectileClickVar->setDamage(3);

        // Setting projectile speed to slower than player1
        projectileClickVar->setStepSize(15);

        // Projectile spawns at player2 pixmap
        projectileClickVar->setPos(m_player2->x()+10,m_player2->y()+10);

        // Finding angle between mouse press and player2 pixmap
        QLineF line(m_player2->pos(),event->pos());
        double projectileAngle = -1 * line.angle();

        // Set rotation using the angle
        projectileClickVar->setRotation(projectileAngle);

        // Add to scene
        m_scene->addItem(projectileClickVar);

        // Score is reduced equal to potential damage of the projectile
        changeScore(-3);
    }
}

void game::setHealth(int input)
{
    m_health = input;
}

void game::changeHealth(int input)
{
    m_health += input;

    // Health cannot decrease below 0
    if(getHealth() < 0)
    {
        setHealth(0);
    }

    m_healthWidget->updateWidget(getHealth());
}

int game::getHealth()
{
    return m_health;
}

void game::setScore(long int input)
{
    m_score = input;
}

void game::changeScore(long int input)
{
    m_score += input;

    // Score cannot decrease below 0
    if(getScore() < 0)
    {
        setScore(0);
    }

    m_scoreWidget->updateWidget(m_score);
}

long int game::getScore()
{
    return m_score;
}

void game::setMsgBoxFlag(bool input)
{
    m_msgBoxFlag = input;
}

bool game::getMsgBoxFlag()
{
    return m_msgBoxFlag;
}

void game::removeInfo()
{
    m_scene->removeItem(m_infoWidget);
}

double game::getPlayer1DelayedXPos()
{
    return m_player1->getDelayedXPos();
}

double game::getPlayer1DelayedYPos()
{
    return m_player1->getDelayedYPos();
}

double game::getPlayer1DelayedDx()
{
    return m_player1->getDelayedDx();
}

double game::getPlayer1DelayedDy()
{
    return m_player1->getDelayedDy();
}

int game::getPlayer1DelayedAngle()
{
    return m_player1->getDelayedAngle();
}




