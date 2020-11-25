#ifndef APP_H
#define APP_H

#include <QObject>
#include <QVector>
#include "user.h"

class App {
    Q_GADGET;
public:
    App();

    bool login(const QString &username, const QString &password);
    bool signup(const User &user);
    User getUser(const QString &username);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    QVector<User> getUsers() const;
    void setUsers(const QVector<User> &ausers);

    void readFromJSON();

    QString getHighscore(QString currUsername);

    void updateUser(User u);

private:
    QVector<User> users;


};

#endif // APP_H
