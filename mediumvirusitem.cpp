#include "mediumvirusitem.h"

/**
 * @brief mediumVirusItem::mediumVirusItem, creates a medium virus
 * @param parent
 * @file mediumvirusitem.h
 */
mediumVirusItem::mediumVirusItem(QObject *parent) : QObject(parent) {
    setPixmap((QPixmap(":/imagesKillCovid/mediumVirus.png")).scaled(130, 130));
}
