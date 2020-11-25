#ifndef MEDIUMVIRUSITEM_H
#define MEDIUMVIRUSITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>

class mediumVirusItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit mediumVirusItem(QObject *parent = nullptr);
};

#endif // MEDIUMVIRUSITEM_H
