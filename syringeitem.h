#ifndef SYRINGEITEM_H
#define SYRINGEITEM_H

#include <QObject>
#include <QtWidgets>

class SyringeItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit SyringeItem(QObject *parent = nullptr);

signals:

};

#endif // SYRINGEITEM_H
