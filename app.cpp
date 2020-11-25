#include "app.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>
#include<QtAlgorithms>


/**
 * @brief App::App, constructor
 * @file app.h
 */
App::App() { }


/**
 * @brief App::readFromJSON, checks if the save.json file exists
 * @file app.h
 */
void App::readFromJSON(){
    if (users.size() == 0) {

        QFile loadFile(QStringLiteral("save.json"));

        if (!loadFile.open(QIODevice::ReadOnly)) {
                qWarning("Couldn't open save file.");
                return;
         }

        QByteArray saveData = loadFile.readAll();

        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

        read(loadDoc.object());
    }

}


/**
 * @brief App::getUsers, returns the vector of users
 * @file app.h
 * @return users
 */
QVector<User> App::getUsers() const {
    return users;
}


/**
 * @brief App::setUsers, sets the vector of users
 * @param ausers
 * @file app.h
 */
void App::setUsers(const QVector<User> &ausers) {
    users = ausers;
}


/**
 * @brief App::login, log in user
 * @file app.h
 * @param username
 * @param password
 * @return true if success
 */
bool App::login(const QString &username, const QString &password) {
    if (users.size() == 0) {
        QFile loadFile(QStringLiteral("save.json"));

        if (!loadFile.open(QIODevice::ReadOnly)) {
            qWarning("Couldn't open save file.");
            return false;
        }

        QByteArray saveData = loadFile.readAll();

        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

        read(loadDoc.object());
    }

    for (int i=0; i<users.size(); i++) {
        User user = users[i];
        if (user.getUsername() == username && user.getPassword() == password) {
            return true;
        }
    }

    return false;
}


/**
 * @brief App::signup, sign up user
 * @param user
 * @return true if success
 * @file app.h
 */
bool App::signup(const User &user) {
    if (users.size() == 0) {
        QFile loadFile("save.json");

        if (loadFile.open(QIODevice::ReadOnly)) {
            QByteArray saveData = loadFile.readAll();

            QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

            read(loadDoc.object());
        }
    }

    QFile saveFile(QStringLiteral("save.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    users.append(user);
    QJsonObject appObj;
    write(appObj);
    QJsonDocument saveDoc(appObj);

    saveFile.write(saveDoc.toJson());

    return true;
}


/**
 * @brief App::getUser, gets the user with the given username
 * @file app.h
 * @param username
 * @return
 */
User App::getUser(const QString &username) {
    for (int i=0; i<users.size(); i++) {
        User user = users[i];
        if (user.getUsername() == username) {
            return user;
        }
    }
    return User();
}

/**
 * @brief App::updateUser, updates the user in the Json after the score gets updated.
 * @file app.h
 * @param u
 */
void App::updateUser(User u){
    int index = -1;
    for (int i=0; i<users.size(); i++) {
        User user = users[i];
        if (user.getUsername() == u.getUsername()) {
            index = i;
            break;
        }
    }

    if (index!=-1){
        users.removeAt(index);
        signup(u);
    }
}

/**
 * @brief App::read, reads the json to get user info
 * @file app.h
 * @param json
 */
void App::read(const QJsonObject &json) {
    if (json.contains("users") && json["users"].isArray()) {
        QJsonArray usersArray = json["users"].toArray();
        users.clear();
        users.reserve(usersArray.size());
        for (int userInd=0; userInd<usersArray.size(); userInd++) {
            QJsonObject userObj = usersArray[userInd].toObject();
            User user;
            user.read(userObj);
            users.append(user);
        }
    }
}


/**
 * @brief App::write, writes to json
 * @file app.h
 * @param json
 */
void App::write(QJsonObject &json) const {
    QJsonArray usersArray;
    foreach (const User user, users) {
        QJsonObject userObj;
        user.write(userObj);
        usersArray.append(userObj);
    }
    json["users"] = usersArray;
}


/**
 * @brief App::getHighscore, gets the highscore of the given username
 * @file app.h
 * @param currUsername
 * @return
 */
QString App::getHighscore(QString currUsername){
    QVector<User> userVector = getUsers();
    int maxScore = 0;
    QString userWithHighscore = "";
    for (User user: userVector) {
        QVector<int> scoresVector = user.getScores();
        for(int score: scoresVector){
            if (score>maxScore){
                maxScore = score;
                userWithHighscore = user.getUsername();
            }
        }
    }
    bool tie = false;
    int usersWithHighscore = 0;
    for (User user: userVector) {
        QVector<int> scoresVector = user.getScores();
        for(int score: scoresVector){
            if (score==maxScore){
                usersWithHighscore++;
            }
        }
        if(usersWithHighscore>1){
            tie = true;
            break;
        }
    }
    User u = getUser(currUsername);
    QString ret;
    if (currUsername == userWithHighscore) {
        ret = "Congratulations! You have the global highscore with " + QString::number(maxScore)+ " points!";
    } else if (u.getHighscore()==maxScore and tie==true){
        ret = "Congratulations! But be aware, you are tied with other player(s) with a highscore of "+ QString::number(maxScore)+ " points!";
    } else {
        ret = "Player " + userWithHighscore + " has the global highscore with " + QString::number(maxScore)+ " points. Keep trying!";
    }
    return ret;
}




