#include "syringeitem.h"
#include <QTimer>

/**
 * @brief SyringeItem::SyringeItem, constructor for the syringe
 * @param parent
 * @file syringeitem.h
 * Sets the syringe, size and rotation.
 */
SyringeItem::SyringeItem(QObject *parent) : QObject(parent) {
    setPixmap((QPixmap(":/imagesKillCovid/syringe.png")).scaled(120, 142));

    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);
    setRotation(rotation()-45);
}
