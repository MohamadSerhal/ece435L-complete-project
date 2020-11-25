#ifndef LARGEVIRUSITEM_H
#define LARGEVIRUSITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>

class largeVirusItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit largeVirusItem(QObject *parent = nullptr);
};

#endif // LARGEVIRUSITEM_H
