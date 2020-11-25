#include "virusitem.h"


/**
 * @brief VirusItem::VirusItem, creates a virus
 * @file virusitem.h
 * @param parent
 * @param type
 * Depending on the type, it creates a small virus (type=0), medium virus (type=1), large virus (type=2).
 */
VirusItem::VirusItem(QObject *parent, int type) : QObject(parent) {
    QString imageStr;
    if (type == 0) {
        imageStr = ":/imagesKillCovid/virus.png";
    } else if (type == 1) {
        imageStr = ":/imagesKillCovid/mediumVirus.png";
    } else {
        imageStr = ":/imagesKillCovid/largeVirus.png";
    }
    setPixmap((QPixmap(imageStr)).scaled(100+type*10, 100+type*10));
}
