#include <QApplication>
#include <QGraphicsView>
#include "introwidget.h"


/**
 * @brief main, the main window
 * @param argc
 * @param argv
 *
 * We open an create and show an instance of IntroWidget
 *
 * @return
 */
int main(int argc,char** argv){
    QApplication app(argc, argv);

    IntroWidget* intro = new IntroWidget();
    intro->setWindowTitle("Kill COVID-19");
    intro->show();

    return app.exec();
}

