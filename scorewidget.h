#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>

class scoreWidget : public QGraphicsTextItem
{
public:
    scoreWidget(QGraphicsItem *parent = nullptr);
    ~scoreWidget();

    void updateWidget(int input);
};

#endif // SCOREWIDGET_H
