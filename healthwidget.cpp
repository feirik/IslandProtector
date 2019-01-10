#include "healthwidget.h"

#include <QFont>

healthWidget::healthWidget(QGraphicsItem *parent)
{
    QFont font("Courier New", 16);

    font.setStyleHint(QFont::Monospace);
    font.setWeight(QFont::Bold);

    setDefaultTextColor(Qt::red);
    setFont(font);
}

healthWidget::~healthWidget()
{

}

void healthWidget::updateWidget(int input)
{
    setPlainText(QString("HP: ") + QString::number(input));
}




