#ifndef STAINITEM_H
#define STAINITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>

class stainItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit stainItem(QObject *parent = nullptr);
};

#endif // STAINITEM_H
