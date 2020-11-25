#include "introwidget.h"

#include <QStyle>
#include <QMediaPlaylist>

#include<settingswidget.h>


/**
 * @brief IntroWidget::IntroWidget
 * @param parent
 * @file introwidget.h
 * constructor that sets the: background, size, widgets, style, layout and connections
 */
IntroWidget::IntroWidget(QWidget *parent) : QWidget(parent) {

    setFixedSize(500, 282);

    setupBackground();
    setupWidgets();
    setupStylesheet();
    setupLayout();
    centerWindow();
    setupConnections();
    setupMusic();

}


/**
 * @brief IntroWidget::setupBackground
 * @file introwidget.h
 * sets up the back ground pictures
 */
void IntroWidget::setupBackground() {
    QPixmap bkgnd(":/imagesKillCovid/intro-background.jpeg");
    bkgnd = bkgnd.scaled(QSize(500, 282), Qt::KeepAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);

    this->setPalette(palette);
}

/**
 * @brief IntroWidget::setupWidgets
 * @file introwidget.h
 * Sets up the buttons and labels.
 */
void IntroWidget::setupWidgets() {
    titleLabel = new QLabel("Kill COVID-19");
    titleLabel->setStyleSheet("color: white;"
                              "font: bold 27px;");
    titleLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    playButton = new QPushButton("Play (or Press F1)");
    playButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}


/**
 * @brief IntroWidget::setupStylesheet
 * @file introwidget.h
 * Sets style of push buttons.
 */
void IntroWidget::setupStylesheet() {
    setStyleSheet("QPushButton {"
                    "background-color: #FFFFFF;"
                    "color: #000000;"
                    "border-radius: 3px;"
                    "min-width: 11em;"
                    "padding: 6px;"
                  "}"
                  "QPushButton:pressed {"
                    "background-color: #C4C4C4;"
                  "}");
}



/**
 * @brief IntroWidget::setupLayout
 * @file introwidget.h
 * Sets layout.
 */
void IntroWidget::setupLayout() {
    QVBoxLayout* innervbox = new QVBoxLayout();
    innervbox->addWidget(titleLabel, 1, Qt::AlignRight);
    innervbox->addWidget(playButton, 0, Qt::AlignRight);

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addStretch(1);
    vbox->addLayout(innervbox);
    vbox->addStretch(1);
}


/**
 * @brief IntroWidget::centerWindow
 * @file introwidget.h
 * Centers window
 */
void IntroWidget::centerWindow() {
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
 * @brief IntroWidget::setupConnections
 * @file introwidget.h
 * Setting the connections.
 */
void IntroWidget::setupConnections() {
    QObject::connect(playButton, SIGNAL(clicked(bool)), this, SLOT(clickPlay()));
}



/**
 * @brief IntroWidget::keyPressEvent
 * @param event
 * When 'F1' is pressed, calls clickPlay()
 */
void IntroWidget::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_F1){
        clickPlay();
    }
}


/**
 * @brief IntroWidget::clickPlay
 * @file introwidget.h
 *
 * When the play button is pressed it opens the settingswidget and closes this one.
 */
void IntroWidget::clickPlay() {
    SettingsWidget* settings = new SettingsWidget();
    settings->setApp(application);
    settings->setUser(user);
    settings->show();
    this->close();
}


/**
 * @brief IntroWidget::setupMusic
 * @file introwidget.h
 *
 * Sets up the music.
 */
void IntroWidget::setupMusic() {
    QMediaPlaylist* playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/intro-music.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    musicPlayer = new QMediaPlayer();
    musicPlayer->setPlaylist(playlist);
    musicPlayer->play();
}


/**
 * @brief IntroWidget::setApp
 * @file introwidget.h
 * @param a
 */
void IntroWidget::setApp(App a){
    application = a;
}


/**
 * @brief IntroWidget::setUser
 * @file introwidget.h
 * @param u
 */
void IntroWidget::setUser(User u){
    user = u;
}
