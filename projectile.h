#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QString>

class projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    projectile(QGraphicsItem *parent=0);
    ~projectile();

    void setStepSize(int input);
    int getStepSize();

    void setDamage(int input);
    int getDamage();

    void updatePixmap(QString directory);

public slots:
    void move();

private:
    int m_stepSize;
    int m_damage;
};

#endif // PROJECTILE_H
