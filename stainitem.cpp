#include "stainitem.h"

/**
 * @brief stainItem::stainItem, constructor for a stain (after virus is killed)
 * @file stainitem.h
 * @param parent
 */
stainItem::stainItem(QObject *parent) : QObject(parent){

    setPixmap((QPixmap(":/imagesKillCovid/stain.png")).scaled(160, 160));
}
