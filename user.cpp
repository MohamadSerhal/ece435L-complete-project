#include "user.h"

#include <QBuffer>

/**
 * @brief User::User, constructor of User
 * @file User.h
 * Creates a User and puts the gender as Female.
 */
User::User() :
    gender(Female) {

}



/**
 * @brief User::getUsername, getter for username
 * @return username
 * @file User.h
 */
QString User::getUsername() const {
    return username;
}


/**
 * @brief User::setUsername, setter for User
 * @param ausername
 * @file User.h
 */
void User::setUsername(const QString &ausername) {
    username = ausername;
}


/**
 * @brief User::getPassword, getter for password.
 * @return password
 * @file User.h
 */
QString User::getPassword() const {
    return password;
}

/**
 * @brief User::setPassword, setter for password.
 * @param apassword
 * @file User.h
 */
void User::setPassword(const QString &apassword) {
    password = apassword;
}


/**
 * @brief User::getFirstName, getter for first name of user.
 * @return firstName
 * @file User.h
 */
QString User::getFirstName() const {
    return firstName;
}

/**
 * @brief User::setFirstName, setter for first name of user
 * @param afirstName
 * @file User.h
 */
void User::setFirstName(const QString &afirstName) {
    firstName = afirstName;
}


/**
 * @brief User::getLastName, getter of user's last name
 * @file User.h
 * @return lastName
 */
QString User::getLastName() const {
    return lastName;
}

/**
 * @brief User::setLastName, setter of user's last name
 * @file User.h
 * @param alastName
 */
void User::setLastName(const QString &alastName) {
    lastName = alastName;
}


/**
 * @brief User::getDateOfBirth, getter of date of birth
 * @file User.h
 * @return dateOfBirth
 */
QDate User::getDateOfBirth() const {
    return dateOfBirth;
}

/**
 * @brief User::setDateOfBirth, setter of date of birth
 * @file User.h
 * @param adateOfBirth
 */
void User::setDateOfBirth(const QDate &adateOfBirth) {
    dateOfBirth = adateOfBirth;
}


/**
 * @brief User::getGender, getter for User gender
 * @file User.h
 * @return gender
 */
User::Gender User::getGender() const {
    return gender;
}

/**
 * @brief User::setGender, setter for User gender
 * @file User.h
 * @param agender
 */
void User::setGender(User::Gender agender) {
    gender = agender;
}


/**
 * @brief User::getProfilePicture, getter for user profile pic
 * @file User.h
 * @return profilePicture
 */
QPixmap User::getProfilePicture() const {
    return profilePicture;
}

/**
 * @brief User::setProfilePicture, setter of user profile pic
 * @file User.h
 * @param aprofilePicture
 */
void User::setProfilePicture(const QPixmap &aprofilePicture) {
    profilePicture = aprofilePicture;
}

/**
 * @brief User::getScores, getter for user's scores
 * @file User.h
 * @return scores
 */
QVector<int> User::getScores() const {
    return scores;
}

/**
 * @brief User::setScores, setter of user scores
 * @file user.h
 * @param ascores
 */
void User::setScores(const QVector<int> &ascores) {
    scores = ascores;
}


/**
 * @brief User::updateScores, updates the score of a user
 * @file user.h
 * @param n
 */
void User::updateScores(int n){
    QVector<int> s = getScores();
    s.push_back(n);
    setScores(s);
}

/**
 * @brief jsonValFromPixmap, encodes the profile pic to save it as JSon
 * @param p
 * @file user.h
 * @return json
 */
QJsonValue jsonValFromPixmap(const QPixmap &p) {
  QBuffer buffer;
  buffer.open(QIODevice::WriteOnly);
  p.save(&buffer, "PNG");
  auto const encoded = buffer.data().toBase64();
  return {QLatin1String(encoded)};
}

/**
 * @brief pixmapFrom, takes a JSon value and returns the corresponding picture.
 * @file user.h
 * @param val
 * @return QPixmap
 */
QPixmap pixmapFrom(const QJsonValue &val) {
  auto const encoded = val.toString().toLatin1();
  QPixmap p;
  p.loadFromData(QByteArray::fromBase64(encoded), "PNG");
  return p;
}


/**
 * @brief User::read, reads user info from JSon.
 * @file user.h
 * @param json
 */
void User::read(const QJsonObject &json) {
    if (json.contains("username") && json["username"].isString()) {
        username = json["username"].toString();
    }
    if (json.contains("password") && json["password"].isString()) {
        password = json["password"].toString();
    }
    if (json.contains("firstName") && json["firstName"].isString()) {
        firstName = json["firstName"].toString();
    }
    if (json.contains("lastName") && json["lastName"].isString()) {
        lastName = json["lastName"].toString();
    }
    if (json.contains("dateOfBirth") && json["dateOfBirth"].isString()) {
        QString s = json["dateOfBirth"].toString();
        QStringList parts = s.split(QString("/"));
        int year = parts.at(0).toInt(), month = parts.at(1).toInt(), day = parts.at(2).toInt();
        dateOfBirth = QDate(year, month, day);
    }
    if (json.contains("gender") && json["gender"].isDouble()) {
        gender = Gender(json["gender"].toInt());
    }
    if (json.contains("profilePicture")) {
        QJsonValue val = json.value("profilePicture");
        profilePicture = pixmapFrom(val);
    }
    if (json.contains("scores") && json["scores"].isArray()) {
        QJsonArray arr = json["scores"].toArray();
        scores.clear();
        scores.reserve(arr.size());
        for (int ind=0; ind<arr.size(); ind++) {
            int score = arr[ind].toInt();
            scores.append(score);
        }
    }
}


/**
 * @brief User::write, writes to JSon the info of a user
 * @file user.h
 * @param json
 */
void User::write(QJsonObject &json) const {
    json["username"] = username;
    json["password"] = password;
    json["firstName"] = firstName;
    json["lastName"] = lastName;
    QString date = "";
    date.append(QString::number(dateOfBirth.year() ));
    date.append("/");
    date.append(QString::number(dateOfBirth.month() ));
    date.append("/");
    date.append(QString::number(dateOfBirth.day()));
    date.append("/");
    json["dateOfBirth"] = date;
    json["gender"] = gender;
    json["profilePicture"] = jsonValFromPixmap(profilePicture);
    QJsonArray scoresArray;
    foreach (const int score, scores) {
        scoresArray.append(score);
    }
    json["scores"] = scoresArray;
}


/**
 * @brief User::getUserScores, getter for a user's scores
 * @file user.h
 * @return user scores
 */
QString User::getUserScores(){
    QVector<int> userScores = getScores();
    qSort(userScores);
    QString scoresStr = "Scores: \n";
    // we will only show the 10 highest scores of the user
    for (int i = userScores.size()-1; i>=userScores.size()-10 and i>=0 ; i--){
        scoresStr = scoresStr + QString::number(userScores[i]) + "pts\n";
    }
    return scoresStr;
}


/**
 * @brief User::getHighscore, getter for a user's highscore
 * @file user.h
 * @return user highscores
 */
int User::getHighscore(){
    QVector<int> userScores = getScores();
    qSort(userScores);
    return userScores[userScores.size()-1];
}
