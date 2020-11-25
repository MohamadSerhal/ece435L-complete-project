#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QtWidgets>
#include "app.h"
#include "user.h"

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView();
    User user;
    App app;
    void setUser(User u);
    void setApp(App a);

private:
    void centerWindow();
};

#endif // GAMEVIEW_H
