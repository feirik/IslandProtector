#ifndef HEALTHWIDGET_H
#define HEALTHWIDGET_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>

class healthWidget : public QGraphicsTextItem
{
public:
    healthWidget(QGraphicsItem *parent = nullptr);
    ~healthWidget();

    void updateWidget(int input);
};

#endif // HEALTHWIDGET_H
