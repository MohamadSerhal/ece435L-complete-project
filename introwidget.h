#ifndef INTROWIDGET_H
#define INTROWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QMediaPlayer>
#include "user.h"
#include "app.h"

class IntroWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IntroWidget(QWidget *parent = nullptr);

    QLabel* titleLabel;
    QPushButton* playButton;

    QMediaPlayer* musicPlayer;

    App application;
    void setApp(App a);
    User user;
    void setUser(User u);

private:
    void centerWindow();
    void setupBackground();
    void setupWidgets();
    void setupStylesheet();
    void setupLayout();
    void setupConnections();
    void setupMusic();
    void keyPressEvent(QKeyEvent *event);


public slots:
    void clickPlay();

signals:

};

#endif // INTROWIDGET_H
