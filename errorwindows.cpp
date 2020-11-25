#include "errorwindows.h"


/**
 * @brief errorWindows::errorWindows constructor that sets the error windows widgets and layout
 * @file errorwindows.h
 * @param parent
 */
errorWindows::errorWindows(QWidget *parent) : QWidget(parent)
{

    errorTitle = new QLabel("ERROR!");
    errorTitle->setStyleSheet("font: 35px;"
                              "color: red;");

    errorMessage = new QLabel();


    verticalLayout = new QVBoxLayout();
    verticalLayout->addWidget(errorTitle);
    verticalLayout->addWidget(errorMessage);

    setLayout(verticalLayout);
}


/**
 * @brief errorWindows::setErrorLabel, sets the error label depending on the kind of error
 * @file errorwindows.h
 * @param error
 */
void errorWindows::setErrorLabel(QString error){
    errorMessage->setText(error);
}
