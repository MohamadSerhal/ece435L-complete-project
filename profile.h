#ifndef PROFILE_H
#define PROFILE_H

#include <QtWidgets>

class profile : public QWidget {
    Q_OBJECT
public:
    explicit profile(QWidget *parent = nullptr);

    QLabel* test;
signals:

};

#endif // PROFILE_H
