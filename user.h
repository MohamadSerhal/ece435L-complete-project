#ifndef USER_H
#define USER_H

#include <QJsonObject>
#include <QString>
#include <QDate>
#include <QImage>
#include <QMap>
#include<QPixmap>
#include <QJsonArray>
#include<QtAlgorithms>

class User {

    Q_GADGET;

public:
    enum Gender {
        Male, Female, Other
    };
    Q_ENUM(Gender)

    User();

    QString getUsername() const;
    void setUsername(const QString &ausername);

    QString getPassword() const;
    void setPassword(const QString &apassword);

    QString getFirstName() const;
    void setFirstName(const QString &afirstName);

    QString getLastName() const;
    void setLastName(const QString &alastName);

    QDate getDateOfBirth() const;
    void setDateOfBirth(const QDate &adateOfBirth);

    Gender getGender() const;
    void setGender(Gender agender);

    QPixmap getProfilePicture() const;
    void setProfilePicture(const QPixmap &aprofilePicture);

    QVector<int> getScores() const;
    void setScores(const QVector<int> &ascores);
    void updateScores(int n);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    QString getUserScores();

    int getHighscore();

private:
    QString username;
    QString password;
    QString firstName;
    QString lastName;
    QDate dateOfBirth;
    Gender gender;
    QPixmap profilePicture;
    QVector<int> scores;
};

#endif // USER_H
