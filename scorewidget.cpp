#include "scorewidget.h"

#include <QFont>

scoreWidget::scoreWidget(QGraphicsItem *parent)
{
    QFont font("Courier New", 16);

    font.setStyleHint(QFont::Monospace);
    font.setWeight(QFont::Bold);

    setDefaultTextColor(Qt::black);
    setFont(font);
}

scoreWidget::~scoreWidget()
{

}

void scoreWidget::updateWidget(int input)
{
    setPlainText(QString("Score: ") + QString::number(input));
}
