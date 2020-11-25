#include "successwindow.h"


/**
 * @brief successWindow::successWindow, constructor for the success window
 * @file successwindow.h
 * @param parent
 */
successWindow::successWindow(QWidget *parent) : QWidget(parent)
{

    sucessLabel = new QLabel("SUCCESS!");
    sucessLabel->setStyleSheet("font: 35px;"
                               "color: green;");
    successMessage = new QLabel();

    verticalLayout = new QVBoxLayout();
    verticalLayout->addWidget(sucessLabel);
    verticalLayout->addWidget(successMessage);

    setLayout(verticalLayout);

}

/**
 * @brief successWindow::setSuccessLabel, sets the success label
 * @file successwindow.h
 * @param str
 */
void successWindow::setSuccessLabel(QString str){
    successMessage->setText(str);
}


/**
 * @brief successWindow::setSuccessLabelPicture, sets the picture in the success window
 * @file successwindow.h
 * @param pic
 */
void successWindow::setSuccessLabelPicture(QPixmap pic){
    successMessage->setPixmap(pic);
}


/**
 * @brief successWindow::changeSuccessLabel, changes the label of the success message
 * @file successwindow.h
 * @param str
 */
void successWindow::changeSuccessLabel(QString str){
    sucessLabel->setText(str);
}
