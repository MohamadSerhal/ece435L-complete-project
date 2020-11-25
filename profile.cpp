#include "profile.h"

/**
 * @brief profile::profile, creates profile
 * @file profile.h
 * @param parent
 */
profile::profile(QWidget *parent) : QWidget(parent) {
    test = new QLabel("Welcome, User!");
}
