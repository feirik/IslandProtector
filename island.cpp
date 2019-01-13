#include "enemy.h"
#include "game.h"
#include "island.h"

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

#include <stdlib.h>

extern game *gameVar;

island::island()
{
    setPixmap(QPixmap(":/images/island.png"));

    m_spawnTimer = new (std::nothrow) QTimer(this);

    if(m_spawnTimer == nullptr)
    {
        qDebug() << "Failed to allocate m_spawnTimer memory";
    }

    m_enemyCount = 0;

    // Seeding random number generator for setting enemy spawn locations in enemy.cpp
    srand(time(NULL));

    connect(m_spawnTimer,SIGNAL(timeout()),this,SLOT(spawnEnemy()));
    m_spawnTimer->start(5000);
}

island::~island()
{

}

void island::setEnemyCount(int input)
{
    m_enemyCount = input;
}

void island::changeEnemyCount(int input)
{
    m_enemyCount += input;
}

int island::getEnemyCount()
{
    return m_enemyCount;
}

void island::spawnEnemy()
{
    // Update spawnTimer to decrease time between spawns in intervals
    if(getEnemyCount() == 10)
    {
        m_spawnTimer->start(4500);
    }
    else if(getEnemyCount() == 20)
    {
        m_spawnTimer->start(4000);
    }
    else if(getEnemyCount() == 30)
    {
        m_spawnTimer->start(3500);
    }
    else if(getEnemyCount() == 40)
    {
        m_spawnTimer->start(3000);
    }
    else if(getEnemyCount() == 50)
    {
        m_spawnTimer->start(2500);
    }
    else if(getEnemyCount() == 75)
    {
        m_spawnTimer->start(1500);
    }

    // Mem freed when enemy collides with players, island or is destroyed by projectiles
    enemy *enemyVar = new (std::nothrow) enemy();

    if(enemyVar == nullptr)
    {
        qDebug() << "Failed to allocate enemyVar memory";
    }

    gameVar->scene()->addItem(enemyVar);
    changeEnemyCount(1);
}
