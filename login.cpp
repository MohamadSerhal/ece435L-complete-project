#include "login.h"
#include <QSizePolicy>
#include "signup.h"
#include<errorwindows.h>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QTextStream>


/**
 * @brief login::login, login window adds the widgets, layout and connections
 * @file login.h
 * @param parent
 */
login::login(QWidget *parent) : QWidget(parent)
{


    logIn = new QLabel("Log In");
    logIn->setStyleSheet("font: 25px;");
    logIn->setAlignment(Qt::AlignCenter);

    username = new QLabel("Username");
    password = new QLabel("Password");

    usernameEdit = new QLineEdit();

    passEdit = new QLineEdit();
    passEdit->setEchoMode(QLineEdit::Password);   // this will hide when inputing the password


    logInButton = new QPushButton("Log In");

    signUpButton = new QPushButton("Sign Up");
    playAsGuestButton = new QPushButton("Play as Guest");

    // Grid Layout
    gridLayout = new QGridLayout();

    gridLayout->addWidget(logIn, 0,0);
    gridLayout->addWidget(username, 1, 0);
    gridLayout->addWidget(usernameEdit, 2, 0);
    gridLayout->addWidget(password, 3,0);
    gridLayout->addWidget(passEdit, 4, 0);
    gridLayout->addWidget(logInButton, 5, 0);

    // Vertical Layout
    verticalLayout = new QVBoxLayout();
    verticalLayout->addItem(gridLayout);
    verticalLayout->addItem(new QSpacerItem(50,50));
    verticalLayout->addWidget(signUpButton);
    verticalLayout->addWidget(playAsGuestButton);

    verticalLayout->setSpacing(20); // spacing between vertical entries in box
    verticalLayout->setMargin(40);

    setLayout(verticalLayout);
    //slots connection

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );

    // when we press the play as guest button
    QObject::connect(playAsGuestButton, SIGNAL(clicked(bool)), this, SLOT(playAsGuestFunc()));
    // when we press the log in button
    QObject::connect(logInButton, SIGNAL(clicked(bool)), this, SLOT(loggingIn()));
    // when we press the sign up button instead
    QObject::connect(signUpButton, SIGNAL(clicked(bool)), this, SLOT(signUpInstead()));

}


/**
 * @brief login::playAsGuestFunc, when the play as guest button is pressed logs in the user as a guest
 * @file login.h
 */
void login::playAsGuestFunc(){
    usernameEdit->setText("Guest");
    passEdit->setText("GuestPassword1");
    User* u = new User();
    login::highscoresPage(0, *u );
}


/**
 * @brief login::loggingIn, after log in is pressed, tries to log in the user
 * @file login.h
 */
void login::loggingIn(){
    QString username = usernameEdit->text();
    QString password = passEdit->text();

    if (app.login(username, password)) {
        User user = app.getUser(username);
        usernameEdit->setText(user.getUsername());
        login::highscoresPage(1, user);
    } else {
        usernameEdit->setText("FAILURE");
        login::openErrorWindow();

    }


}


/**
 * @brief login::signUpInstead, user pressed the button to go sign up instead
 * @file login.h
 */
void login::signUpInstead(){

    signUp* signUpWindow = new signUp();
    signUpWindow->show();
    this->close();
}

/**
 * @brief login::highscoresPage, logs in user succesffuly to the highscore window
 * @file login.h
 * @param code
 * @param user
 */
void login::highscoresPage(int code, User user){
    // if code is zero, thn log in as guest
    highscoresWindow* highWindow = new highscoresWindow(app, code, user);
    highWindow->show();
    this->close();
}


/**
 * @brief login::openErrorWindow, gives error if username or password is incorrect
 * @file login.h
 */
void login::openErrorWindow(){
    errorWindows* errorW = new errorWindows();
    errorW->setErrorLabel("Username or Password is incorrect!");
    errorW->show();

}

