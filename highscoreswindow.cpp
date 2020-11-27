#include "othelloview.h"
#include "highscoreswindow.h"
#include "introwidget.h"

/**
 * @brief highscoresWindow::highscoresWindow constructor
 * @file highscoreswindow.h
 * @param app
 * @param code
 * @param user
 * @param parent
 */
highscoresWindow::highscoresWindow(App app, int code, User user, QWidget *parent) : QWidget(parent)
{
    useri = user;
    apli = app;

    QDate userBirthday = user.getDateOfBirth();
    QString userBirthdayString = userBirthday.toString();
    checkIfBirthday(userBirthdayString);

    profilePicLabel = new QLabel();
    profilePicLabel->setAlignment(Qt::AlignCenter);

    welcomeLabel = new QLabel();
    usernameLabel = new QLabel();
    usernameLabel->setStyleSheet("font: 30px;");
    usernameLabel->setAlignment(Qt::AlignCenter);

    // these widgets will be on the right

    globalHighscorePlayerLabel = new QLabel(app.getHighscore(user.getUsername()));
    globalHighscorePlayerLabel->setAlignment(Qt::AlignCenter);
    userScoresLabel = new QLabel();
    userScoresLabel->setAlignment(Qt::AlignCenter);
    compareScoresLabel = new QLabel();
    compareScoresLabel->setAlignment(Qt::AlignCenter);


    // code==0 then play as guest
    if (code == 0){
        playAsGuest();
    }

    if(code == 1){
        playAsUser(user);
    }

    gridLayout = new QGridLayout();

    groupBoxLeft = new QGroupBox();
    groupBoxRight = new QGroupBox();

    playKillCovidButton = new QPushButton("Play Kill-Covid");
    playOrthelloButton = new QPushButton("Play Othello");

    // setting the vertical layout on the left
    verticalLayoutLeft = new QVBoxLayout();
    verticalLayoutLeft->addWidget(profilePicLabel);
    verticalLayoutLeft->addWidget(usernameLabel);
    verticalLayoutLeft->addWidget(welcomeLabel);
    verticalLayoutLeft->addWidget(playKillCovidButton);
    verticalLayoutLeft->addWidget(playOrthelloButton);

    verticalLayoutLeft->setAlignment(playKillCovidButton, Qt::AlignCenter);
    verticalLayoutLeft->setAlignment(playOrthelloButton, Qt::AlignCenter);

    // widgets that will be on the right
    highscoreLabel = new QLabel("RANKING");
    highscoreLabel->setStyleSheet("font: 20px;");
    highscoreLabel->setAlignment(Qt::AlignCenter);



    // setting the vertical layout on the right
    verticalLayoutRight = new QVBoxLayout();
    verticalLayoutRight->addWidget(highscoreLabel);
    verticalLayoutRight->addWidget(globalHighscorePlayerLabel);
    verticalLayoutRight->addWidget(userScoresLabel);
    verticalLayoutRight->addWidget(compareScoresLabel);

    // setting the layout of the group boxes
    groupBoxLeft->setLayout(verticalLayoutLeft);
    groupBoxRight->setLayout(verticalLayoutRight);


    // setting the grid layout
    gridLayout->addWidget(groupBoxLeft, 0, 0);
    gridLayout->addWidget(groupBoxRight, 0, 1);

    setLayout(gridLayout);

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );

    // connect buttons
    QObject::connect(playOrthelloButton, SIGNAL(clicked(bool)), this, SLOT(clickOrthello()));
    QObject::connect(playKillCovidButton, SIGNAL(clicked(bool)), this, SLOT(clickKillCovid()));

}



//
/**
 * @brief highscoresWindow::checkIfBirthday, if it's the user's birthday display a "Happy Birthday message"
 * @file highscoreswindow.h
 * @param birthdayStr
 */
void highscoresWindow::checkIfBirthday(QString birthdayStr){
    QDate currentDate = QDate::currentDate();
    QString dateString = currentDate.toString();

    if (QString::compare(dateString , birthdayStr)==0){
        successWindow* succW = new successWindow();
        succW->changeSuccessLabel("TODAY IS YOUR BIRTHDAY! ");
        succW->setSuccessLabelPicture(QPixmap(":/images/banner-happy-birthday.png"));
        succW->show();
    }

}


/**
 * @brief highscoresWindow::playAsGuest, fixes the widgets to show generic guest info
 * @file highscoreswindow.h
 */
void highscoresWindow::playAsGuest(){
    profilePicLabel->setPixmap(QPixmap(":/images/User_icon.png").scaled(200, 200));
    usernameLabel->setText("Guest");
    welcomeLabel->setText("We welcome you as a guest! Hope you enjoy!");
    userScoresLabel->setText("Scores: \n Sign up to play and see your scores!");

}


/**
 * @brief highscoresWindow::playAsUser, fixes the widgets to show user info
 * @file highscoreswindow.h
 * @param user
 */
void highscoresWindow::playAsUser(User user){
    // getting the user info
    QString username = user.getUsername();
    QString firstName = user.getFirstName();
    QString lastName = user.getLastName();

    QPixmap profilePic = user.getProfilePicture();

    welcomeLabel->setText( "Welcome back, " + firstName +" "+ lastName + "!");
    usernameLabel->setText(username);
    profilePicLabel->setPixmap(profilePic);
    userScoresLabel->setText(user.getUserScores());


}


/**
 * @brief highscoresWindow::clickKillCovid, user to play kill covid 19
 * @file highscoreswindow.h
 */
void highscoresWindow::clickKillCovid(){
    IntroWidget* i = new IntroWidget();
    i->setApp(apli);
    i->setUser(useri);
    i->show();
    this->close();
    this->~highscoresWindow();
}


/**
 * @brief highscoresWindow::clickOrthello, user click on button to play Orthello
 * @file highscoreswindow.h
 */
void highscoresWindow::clickOrthello(){
    othelloView* view = new othelloView();
    view->show();
    this->close();
    this->~highscoresWindow();
}

