#include "settingswidget.h"

#include <QGraphicsView>
#include <gameview.h>


/**
 * @brief SettingsWidget::SettingsWidget, constructor
 * @param parent Parent widget
 * @file settingswidget.h
 * constructor that sets the: background, widgets, style, layout and connections
 */
SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent) {
    vbox = new QVBoxLayout(this);
    readyButtonAvailable = false;
    difficultyChosen = "";
    setupBackground();
    setupWidgets();
    setupStylesheet();
    setupLayout();
    centerWindow();
    setupConnections();


}


/**
 * @brief SettingsWidget::setupBackground, sets up backgroud
 * @file settingswidget.h
 * sets the background picture
 */
void SettingsWidget::setupBackground() {
    QPixmap bkgnd(":/imagesKillCovid/intro-background.jpeg");
   // bkgnd = bkgnd.scaled(QSize(2000, 1100), Qt::KeepAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);

    this->setPalette(palette);
}



/**
 * @brief SettingsWidget::setupWidgets, sets up widgets
 * @file settingswidget.h
 * Sets the labels and push buttons
 */
void SettingsWidget::setupWidgets() {

    titleLabel = new QLabel("Choose your difficulty");
    titleLabel->setStyleSheet("color: white;"
                              "font: bold 27px;");
    titleLabel->setAlignment(Qt::AlignCenter);

    easyButton = new QPushButton("Easy");
    mediumButton = new QPushButton("Medium");
    hardButton = new QPushButton("Hard");
    readyButton = new QPushButton("Ready");
    howToPlayButton = new QPushButton("HELP");

    explainDiffLabel = new QLabel();
    explainDiffLabel->setAlignment(Qt::AlignCenter);
    explainDiffLabel->setStyleSheet("color: white;"
                                    "font: bold 20px;"
                                    );

}



/**
 * @brief SettingsWidget::setupStylesheet
 * @file settingswidget.h
 * Styling the push buttons
 */
void SettingsWidget::setupStylesheet() {
    setStyleSheet("QPushButton {"
                    "background-color: #FFFFFF;"
                    "color: #000000;"
                    "border-radius: 3px;"
                    "min-width: 11em;"
                    "padding: 6px;"
                    "max-width: 500px;"
                    "text-align: "
                  "}"
                  "QPushButton:pressed {"
                    "background-color: #C4C4C4;"
                  "}");
}


/**
 * @brief SettingsWidget::setupLayout
 * @file settingswidget.h
 * Setting the layout
 */
void SettingsWidget::setupLayout() {

    vbox->addWidget(titleLabel);
    vbox->addWidget(easyButton);
    vbox->addWidget(mediumButton);
    vbox->addWidget(hardButton);
    vbox->addWidget(howToPlayButton);
    vbox->addWidget(explainDiffLabel);

    vbox->setAlignment(easyButton, Qt::AlignHCenter);
    vbox->setAlignment(mediumButton, Qt::AlignHCenter);
    vbox->setAlignment(hardButton, Qt::AlignHCenter);
    vbox->setAlignment(howToPlayButton, Qt::AlignHCenter);
}


/**
 * @brief SettingsWidget::setupConnections
 * @file settingswidget.h
 * Connecting easy button to its slot clickEasy()
 * Connecting medium button to its slot clickMedium()
 * Connecting hard button to its slot clickHard()
 * Connecting the ready button to the clickReady() slot
 */
void SettingsWidget::setupConnections(){
    // When we press a difficulty button the ready button should appear
    QObject::connect(easyButton, SIGNAL(clicked(bool)), this, SLOT(clickEasy()));
    QObject::connect(mediumButton, SIGNAL(clicked(bool)), this, SLOT(clickMedium()));
    QObject::connect(hardButton, SIGNAL(clicked(bool)), this, SLOT(clickHard()));

    // when we press how to play
    QObject::connect(howToPlayButton, SIGNAL(clicked(bool)), this, SLOT(clickHowTo()));

    // when we press the ready button
    QObject::connect(readyButton, SIGNAL(clicked(bool)), this, SLOT(clickReady()));
}


/**
 * @brief SettingsWidget::centerWindow
 * @file settingswidget.h
 * Centering the window
 */
void SettingsWidget::centerWindow() {
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );
}



/**
 * @brief SettingsWidget::clickEasy
 * @file settingswidget.h
 * When the easy button is clicked, it shows the difficulty description,
 * sets the difficulty to easy and shows the ready button
 */
void SettingsWidget::clickEasy(){
    explainDiffLabel->setText("For beginners: the virus starts slow!");
    difficultyChosen = "Easy";
    showReadyButton();
}



/**
 * @brief SettingsWidget::clickMedium
 * @file settingswidget.h
 * When the medium button is clicked, it shows the difficulty description,
 * sets the difficulty to medium and shows the ready button
 */
void SettingsWidget::clickMedium(){
    explainDiffLabel->setText("For experienced players: the virus is fast and gets faster!");
    difficultyChosen = "Medium";
    showReadyButton();
}


/**
 * @brief SettingsWidget::clickHard
 * @file settingswidget.h
 * When the hard button is clicked, it shows the difficulty description,
 * sets the difficulty to hard and shows the ready button
 */
void SettingsWidget::clickHard(){
     explainDiffLabel->setText("For the pros: virus starts moving at break neck speed and only gets faster!");
     difficultyChosen = "Hard";
     showReadyButton();
}


void SettingsWidget::clickHowTo(){
    howToPlayWindow* howTo = new howToPlayWindow();
    howTo->show();
}


/**
 * @brief SettingsWidget::clickReady
 * @file settingswidget.h
 */
void SettingsWidget::clickReady(){
    GameView* view = new GameView();
    view->setApp(apli);
    view->setUser(useri);
    view->show();
    this->close();
}


/**
 * @brief SettingsWidget::showReadyButton
 * @file settingswidget.h
 * If the ready button isn't shown yet, it adds it to the window
 */
void SettingsWidget::showReadyButton(){
    // check first if we already added the ready button to not add it every time
    if(readyButtonAvailable==false){
        readyButtonAvailable=true;
        vbox->addWidget(readyButton);
        vbox->setAlignment(readyButton, Qt::AlignHCenter);
    }
}


/**
 * @brief SettingsWidget::setApp
 * @file settingswidget.h
 * @param a
 */
void SettingsWidget::setApp(App a){
    apli = a;
}

/**
 * @brief SettingsWidget::setUser
 * @file settingswidget.h
 * @param u
 */
void SettingsWidget::setUser(User u){
    useri = u;
}

