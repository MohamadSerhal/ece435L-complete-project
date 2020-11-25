#include "howtoplaywindow.h"


/**
 * @brief howToPlayWindow::howToPlayWindow, constructor, calls functions to center window, setup background, setup widgets and layout
 * @param parent
 * @file howtoplaywindow.h
 */
howToPlayWindow::howToPlayWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(500, 282);
    centerWindow();
    setupBackground();
    setupWidgets();
    setupLayout();


}

/**
 * @brief howToPlayWindow::setupBackground, stes the background image
 * @file howtoplaywindow.h
 */
void howToPlayWindow::setupBackground() {
    QPixmap bkgnd(":/imagesKillCovid/intro-background.jpeg");
    bkgnd = bkgnd.scaled(QSize(500, 282), Qt::KeepAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);

    this->setPalette(palette);
}


/**
 * @brief howToPlayWindow::centerWindow, centers the window
 * @file howtoplaywindow.h
 */
void howToPlayWindow::centerWindow() {
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
 * @brief howToPlayWindow::setupWidgets, sets up the widgets
 * @file howtoplaywindow.h
 */
void howToPlayWindow::setupWidgets(){
    titleLabel = new QLabel("How To Play");
    titleLabel->setStyleSheet("color: white;"
                              "font: bold 27px;");
    titleLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    explainLabel = new QLabel(" - Press LEFT to shoot the syringe \n- Player loses the game after 3 misses");
    explainLabel->setStyleSheet("color: white;"
                              "font: 15px;");
    titleLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}


/**
 * @brief howToPlayWindow::setupLayout, sets up the layout
 * @file howtoplaywindow.h
 */
void howToPlayWindow::setupLayout(){
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->addWidget(titleLabel);
    verticalLayout->addWidget(explainLabel);

    verticalLayout->setAlignment(titleLabel, Qt::AlignHCenter);
    verticalLayout->setAlignment(explainLabel, Qt::AlignHCenter);
}
