#ifndef SIGNUP_H
#define SIGNUP_H

#include<QObject>
#include <QWidget>
#include<QtWidgets>
#include<QFileDialog>

#include "app.h"
#include "user.h"

class signUp : public QWidget
{
    Q_OBJECT
public:
    explicit signUp(QWidget *parent = nullptr);


private:

    QLabel* sign_up;
    QLabel* first_name;
    QLabel* last_name;
    QLabel* username;
    QLabel* password;
    QLabel* confirm_password;
    QLabel* date_of_birth;
    QLabel* gender;
    QLabel* profile_pic;
    QLabel* browse_pic;

    QLineEdit* firstName_edit;
    QLineEdit* lastName_edit;
    QLineEdit* username_edit;
    QLineEdit* password_edit;
    QLineEdit* confirm_edit;

    QCalendarWidget* date_birth_calendar;

    QPushButton* submit_btn;
    QPushButton* back_to_login;
    QPushButton* browse_button;

    QGroupBox* gender_radio_buttons_box;
    QGroupBox* picture_box;

    QRadioButton* gender_male;
    QRadioButton* gender_female;
    QRadioButton* gender_other;

    QVBoxLayout* vertical_layout;
    QVBoxLayout* buttons_vertical_layout;
    QVBoxLayout* picture_vertical_layout;
    QGridLayout* grid_layout;

    App app;




signals:

private slots:
    void login_instead();
    void upload_picture();
    void signup();
    void invalid(QLabel* label, int errorCode);
    bool validate_Username();    // returns false when invalid
    bool validate_password();    // returns false when invalid
};

#endif // SIGNUP_H
