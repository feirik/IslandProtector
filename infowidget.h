#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QObject>

class infoWidget : public QGraphicsTextItem
{
    Q_OBJECT
public:
    infoWidget(QGraphicsItem *parent = nullptr);
    ~infoWidget();

public slots:
    void removeWidget();

private:
    QTimer* m_hideInfoTimer;
};

#endif // INFOWIDGET_H
