#include "game.h"
#include "infowidget.h"

#include <QDebug>
#include <QFont>

extern game *gameVar;

infoWidget::infoWidget(QGraphicsItem *parent)
{
    setPlainText(QString("Defend the island!\n\n"
                         "ARROW UP: Accelerate\n"
                         "ARROW LEFT: Turn left\n"
                         "ARROW RIGHT: Turn right\n"
                         "ARROW DOWN: Slow down\n"
                         "SPACEBAR: Shoot"));

    QFont font("Courier New", 12);

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
