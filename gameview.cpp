#include "gameview.h"

#include <gamescene.h>

/**
 * @brief GameView::GameView constructor
 * @file gameview.h
 */
GameView::GameView() {
    setFixedSize(1280, 720);
    setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));

    GameScene* scene = new GameScene();
    scene->setApp(app);
    scene->setUser(user);
    setScene(scene);

    centerWindow();
}

/**
 * @brief GameView::centerWindow, centers the window
 * @file gameview.h
 */
void GameView::centerWindow() {
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );
}

void GameView::setApp(App a){
    app = a;

}

void GameView::setUser(User u){
    user = u;
}
