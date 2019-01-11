#include "game.h"
#include "infowidget.h"

#include <QDebug>
#include <QFont>

extern game *gameVar;

infoWidget::infoWidget(QGraphicsItem *parent)
{
    setPlainText(QString("Player 1:\n"
                         "ARROW UP: Accelerate\n"
                         "ARROW LEFT: Turn left\n"
                         "ARROW RIGHT: Turn right\n"
                         "ARROW DOWN: Slow down\n"
                         "SPACEBAR: Shoot\n\n"
                         "Player 2:\n"
                         "Use mouse pointer to aim\n"
                         "LEFT MOUSE BUTTON: Shoot\n\n\n\n\n\n\n"
                         "Defend the island!"));

    QFont font("Courier New", 10);

    font.setStyleHint(QFont::Monospace);
    font.setWeight(QFont::Bold);

    setDefaultTextColor(Qt::black);
    setFont(font);

    m_hideInfoTimer = new (std::nothrow) QTimer(this);

    if(m_hideInfoTimer == nullptr)
    {
        qDebug() << "Failed to allocate m_hideInfoTimer memory";
    }

    connect(m_hideInfoTimer,SIGNAL(timeout()),this,SLOT(removeWidget()));
    m_hideInfoTimer->start(7000);
}

infoWidget::~infoWidget()
{

}

void infoWidget::removeWidget()
{
    gameVar->removeInfo();
    delete(this);
}
