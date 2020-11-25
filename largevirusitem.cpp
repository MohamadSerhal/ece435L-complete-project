#include "largevirusitem.h"

/**
 * @brief largeVirusItem::largeVirusItem, constructor, creates a large virus
 * @file largevirusitem.h
 * @param parent
 */
largeVirusItem::largeVirusItem(QObject *parent) : QObject(parent) {
    setPixmap((QPixmap(":/imagesKillCovid/largeVirus.png")).scaled(160, 160));
}

