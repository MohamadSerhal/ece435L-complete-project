#include<QApplication>
#include<login.h>
#include<signup.h>
#include<QMainWindow>


/**
 * @brief main, main method of the application
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv){

    QApplication app(argc, argv);
    login logmain;
    logmain.show();

    return app.exec();
}
