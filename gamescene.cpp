#include "gamescene.h"
#include <QtMath>

/**
 * @brief GameScene::GameScene, constructor calls the functions
 * @file gamescene.h
 */
GameScene::GameScene() {

    setupBackground();
    setupConfig();
    setupState();
    setupItems();
    startTimer();

}


/**
 * @brief GameScene::setupBackground, sets the background image
 * @file gamescene.h
 */
void GameScene::setupBackground() {
    setBackgroundBrush(QBrush(QImage(":/imagesKillCovid/background.png").scaledToHeight(720).scaledToWidth(1280)));
    setSceneRect(0,0,1280,720);

    setFocus();
}


/**
 * @brief GameScene::setupConfig, sets the config file that contains the position and types of the viruses
 * @file gamescene.h
 */
void GameScene::setupConfig() {
    QFile file(":/config/config.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    winningScore = in.readLine().toInt();
    maxMisses = in.readLine().toInt();

    viruses = new QVector<QPair<int, int>*>();

    for (int i=0; i<100; i++) {
        QStringList s = in.readLine().split(" ");
        viruses->append(new QPair<int, int>(s[0].toInt(), s[1].toInt()));
    }

}


/**
 * @brief GameScene::setupState, sets up the initial states of the score and counters
 * @file gamescene.h
 */
void GameScene::setupState() {

    virusCounter = 0;
    misses = 0;
    smallScore = 0;
    mediumScore = 0;
    largeScore = 0;
    totalScore = 0;
    syringeSide = 1;  // starts at the right side
    waiting = 0;
    virusType = 0;
    syringeDirection = 0.5;
    fallingRate = 0.1;
    hitVirus = false;
    syringeShot = false;
    killedViruses = 0;


}


/**
 * @brief GameScene::setupItems, adds the virus and syringe item to the scene. Also adds the score counters.
 * @file gamescene.h
 */
void GameScene::setupItems() {
    syringe = new SyringeItem();
    syringe->setPos(800, 500);
    addItem(syringe);

    virus = new VirusItem(nullptr, viruses->at(virusCounter)->second);
    virus->setPos(400, viruses->at(virusCounter)->first);
    virusCounter++;

    addItem(virus);

    stain = new stainItem();

    missesLabel = new QLabel("Misses : "+ QString::number(misses));
    missesLabel->setStyleSheet("font: 27px;");
    QGraphicsProxyWidget * missesItem = addWidget(missesLabel);
    missesItem->setPos(100, 50);

    smallCounterLabel = new QLabel("Small kills : "+ QString::number(smallScore));
    smallCounterLabel->setStyleSheet("font: 27px;");
    QGraphicsProxyWidget * smallItem = addWidget(smallCounterLabel);
    smallItem->setPos(100, 100);

    mediumCounterLabel= new QLabel("Medium kills : "+ QString::number(mediumScore));
    mediumCounterLabel->setStyleSheet("font: 27px;");
    QGraphicsProxyWidget * medItem = addWidget(mediumCounterLabel);
    medItem->setPos(100, 150);

    largeCounterLabel= new QLabel("Large kills : "+ QString::number(largeScore));
    largeCounterLabel->setStyleSheet("font: 27px;");
    QGraphicsProxyWidget * largeItem = addWidget(largeCounterLabel);
    largeItem->setPos(100, 200);

    totalCounterLabel= new QLabel("Total score : 000");
    totalCounterLabel->setStyleSheet("font: 27px;");
    QGraphicsProxyWidget * totalItem = addWidget(totalCounterLabel);
    totalItem->setPos(100, 250);

}

/**
 * @brief GameScene::keyPressEvent, if user presses left key and the syringe is not in flight, make syringeShot true
 * @param event
 * @file gamescene.h
 */
void GameScene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left && waiting == 0) {
        syringeShot = true;
    }
}


/**
 * @brief GameScene::startTimer, starts a timer that signals the moment to update the screen
 * @file gamescene.h
 */
void GameScene::startTimer() {
    updateTimer = new QTimer();
    QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateScene()));
    updateTimer->start(10);
}


/**
 * @brief GameScene::updateScene, updates scene such like collision with virus, scores, misses and position of syringe
 * @file gamescene.h
 */
void GameScene::updateScene() {
    if (waiting > 0) {
        if (waiting < 100) {
            waiting++;
            return;
        }

        removeItem(popupItem);

        if (hitVirus) removeItem(stain);
        hitVirus = false;

        syringeShot = false;
        syringeSide = 1-syringeSide;
        syringeDirection = 0.5;
        virusType = (virusType + 1) % 3;

        syringe->setRotation(syringeSide == 1 ? -45 : 45);
        syringe->setPos(400 + syringeSide * 400, 500);
        addItem(syringe);

        virus = new VirusItem(nullptr, viruses->at(virusCounter)->second);
        virus->setPos(400 + (1-syringeSide) * 400, viruses->at(virusCounter)->first);
        virusCounter++;

        addItem(virus);

        waiting = 0;
        return;

    }

    bool outOfBounds = (syringe->y() < -200)
            || (syringe->y() > 720)
            || (syringeSide && syringe->x() <= 400)
            || (!syringeSide && syringe->x() >= 800);

    if (!syringeShot && !outOfBounds) {

        if (abs(syringe->rotation()) == 90 || abs(syringe->rotation()) == 20) {
            syringeDirection = - syringeDirection;
        }
        syringe->setRotation(syringe->rotation() + syringeDirection);

    } else {

        int moveDirection = syringeSide ? 1 : -1;
        int newX = syringe->x() - moveDirection * 7;
        int newY = syringe->y()+qTan(qDegreesToRadians(90 - moveDirection * syringe->rotation()))*7;
        syringe->setPos(newX, newY);

        QList<QGraphicsItem*> collided = syringe->collidingItems();

        if (collided.size() == 0 && !outOfBounds) return;


        if (outOfBounds) {

            misses++;

        } else {

            hitVirus = true;
            killedViruses++;

            if (fallingRate < 1.6 && killedViruses != 0 && killedViruses%5 == 0) fallingRate *= 2;

            VirusItem* collidedVirus = (VirusItem*) collided[0];
            if (collidedVirus != virus) {
                qInfo() << "Collided virus doesn't match virus!!!";
            }

            if (virusType == 0) {
                smallScore++;
            } else if (virusType == 1) {
                mediumScore++;
            } else {
                largeScore++;
            }

            stain->setPos(virus->x(), virus->y());
            addItem(stain);

        }

        removeItem(virus);
        removeItem(syringe);
        waiting = 1;

        // Updating score: To win the game, the player must collect 150 points regardless of the counter.
        // If the total score is more than a 150, the last shot is excluded and the games continues.
        // The player keeps shooting until the total score is exactly 150.
        int newScore = smallScore*3 + mediumScore*5 + largeScore*7;
        if (newScore <= 150) {
            totalScore = newScore;
        }

        QString totalStr = QString::number(totalScore);
        int sz = totalStr.size();
        for (int i=0; i<3-sz; i++) {
            totalStr = "0" + totalStr;
        }

        smallCounterLabel->setText("Small kills : " + QString::number(smallScore));
        mediumCounterLabel->setText("Medium kills : " + QString::number(mediumScore));
        largeCounterLabel->setText("Large kills : " + QString::number(largeScore));
        totalCounterLabel->setText("Total score : " + totalStr);
        missesLabel->setText("Misses : " + QString::number(misses));

        if (totalScore == 150) {
            QLabel* popupLabel = new QLabel("You win!");
            popupLabel->setStyleSheet("font: 100px");
            popupItem = addWidget(popupLabel);
            popupItem->setPos(640-(popupItem->rect().width()/2), 320);
            updateTimer->stop();
            finalScore = totalScore;
            updateAppJSon();
            return;
        }

        if (misses == 3 || virusCounter == 100) {
            QLabel* popupLabel = new QLabel("You lose!");
            popupLabel->setStyleSheet("font: 100px");
            popupItem = addWidget(popupLabel);
            popupItem->setPos(640-(popupItem->rect().width()/2), 320);
            updateTimer->stop();
            finalScore = totalScore;
            updateAppJSon();
            return;
        }

        QLabel* popupLabel = new QLabel(hitVirus ? "Hit!" :  "Missed!");
        popupLabel->setStyleSheet("font: 100px");
        popupItem = addWidget(popupLabel);
        popupItem->setPos(640-(popupItem->rect().width()/2), 320);
    }

    syringe->setPos(syringe->x(), syringe->y()+fallingRate);
    virus->setPos(virus->x(), virus->y()+fallingRate);

}

void GameScene::setApp(App a){
    app = a;
}

void GameScene::setUser(User u){
    user = u;
}


void GameScene::updateAppJSon(){
    user.updateScores(finalScore);
    app.updateUser(user);
}
