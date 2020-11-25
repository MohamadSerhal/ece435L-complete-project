#include "signup.h"
#include "login.h"
#include"successwindow.h"
#include"errorwindows.h"

/**
 * @brief signUp::signUp, constructor sets the widgets, layouts and connections
 * @file signup.h
 * @param parent
 */
signUp::signUp(QWidget *parent) : QWidget(parent)
{

    sign_up = new QLabel("Sign Up");
    sign_up->setStyleSheet("font: 25px;");
    sign_up->setAlignment(Qt::AlignCenter);

    first_name = new QLabel("First Name");

    last_name = new QLabel("Last Name");

    username = new QLabel("Username");

    password = new QLabel("Password");

    confirm_password = new QLabel("Confirm Password");

    date_of_birth = new QLabel("Date Of Birth");

    profile_pic = new QLabel("Profile Picture");

    gender = new QLabel("Gender");

    // label that will hold the picture, and its default form
    browse_pic = new QLabel();
    browse_pic->setPixmap(QPixmap(":/images/User_icon.png").scaled(150, 150));


    date_birth_calendar = new QCalendarWidget();

    gender_male = new QRadioButton("Male");
    gender_female = new QRadioButton("Female");
    gender_other = new QRadioButton("Other");

    buttons_vertical_layout = new QVBoxLayout();
    buttons_vertical_layout->addWidget(gender_male);
    buttons_vertical_layout->addWidget(gender_female);
    buttons_vertical_layout->addWidget(gender_other);
    gender_radio_buttons_box = new QGroupBox();
    gender_radio_buttons_box->setLayout(buttons_vertical_layout);

    firstName_edit = new QLineEdit();
    lastName_edit = new QLineEdit();
    username_edit = new QLineEdit();
    password_edit = new QLineEdit();
    password_edit->setEchoMode(QLineEdit::Password);
    confirm_edit = new QLineEdit();
    confirm_edit->setEchoMode(QLineEdit::Password);


    back_to_login = new QPushButton("Back to Log In");
    submit_btn = new QPushButton("Submit");

    browse_button = new QPushButton("Browse For Picture");

    picture_vertical_layout = new QVBoxLayout();
    picture_vertical_layout->addWidget(browse_pic);
    picture_vertical_layout->addWidget(browse_button);
    picture_box = new QGroupBox();
    picture_box->setLayout(picture_vertical_layout);

    // grid layout
    grid_layout = new QGridLayout();
    grid_layout->addWidget(sign_up, 0, 0, 1, 3);
    grid_layout->addWidget(first_name, 1, 0);
    grid_layout->addWidget(firstName_edit, 1, 1);
    grid_layout->addWidget(last_name, 2, 0);
    grid_layout->addWidget(lastName_edit, 2, 1);
    grid_layout->addWidget(username, 3, 0);
    grid_layout->addWidget(username_edit, 3, 1);
    grid_layout->addWidget(password, 4, 0);
    grid_layout->addWidget(password_edit, 4, 1);
    grid_layout->addWidget(confirm_password, 5, 0);
    grid_layout->addWidget(confirm_edit, 5, 1);
    grid_layout->addWidget(date_of_birth, 6, 0);
    grid_layout->addWidget(date_birth_calendar, 6, 1);
    grid_layout->addWidget(gender, 7, 0);
    grid_layout->addWidget(gender_radio_buttons_box, 7, 1);
    grid_layout->addWidget(profile_pic, 8, 0);
    grid_layout->addWidget(picture_box, 8, 1);
    grid_layout->addWidget(submit_btn, 9, 0, 9, 2);

    grid_layout->setVerticalSpacing(2);



    // vertical layout
    vertical_layout =new QVBoxLayout();
    vertical_layout->addItem(grid_layout);
    vertical_layout->addWidget(back_to_login);
    vertical_layout->setMargin(20);


    // set overall layout
    setLayout(vertical_layout);

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );


    // loading the users
    app.readFromJSON();

    // connect the login button
    QObject::connect(back_to_login, SIGNAL(clicked(bool)), this, SLOT(login_instead()));
    // Let's user browse for his/her own picture to add
    QObject::connect(browse_button, SIGNAL(clicked(bool)), this, SLOT(upload_picture()));
    //sign up
    QObject::connect(submit_btn, SIGNAL(clicked(bool)), this, SLOT(signup()));
    // check if username already exists
    QObject::connect(username_edit, SIGNAL(editingFinished()), this, SLOT(validate_Username()));

    // check if password has requirements
    QObject::connect(password_edit, SIGNAL(editingFinished()), this, SLOT(validate_password()));

}


/**
 * @brief signUp::validate_Username, checks if the username is valid
 * @file signup.h
 * @return bool
 * if a Username has a space or is already taken, returns false
 */
bool signUp::validate_Username(){
    // check if username already taken
    bool taken = false;
    bool hasSpace = false;
    QString usernameStr = username_edit->text();
    QVector<User> users = app.getUsers();
    for (User user: users ){
        QString userName = user.getUsername();
        if(QString::compare(userName, usernameStr)==0 ){
            taken = true;
            break;
        }
    }
    if(taken == true ){
        signUp::invalid(username, 1);
        return false;
    }
    for(int i =0 ; i<usernameStr.size(); i++){
        if (usernameStr[i] == ' '){
            hasSpace = true;
            break;
        }
    }
    if(hasSpace==true){
        signUp::invalid(username, 2);
        return false;
    }

    return true;
}



/**
 * @brief signUp::validate_password, checks if pass word is valid.
 * @file signup.h
 * @return bool
 * if a password has size<8, or doesnt have atleast: one number, one upper letter and one lower letter, returns false
 */
bool signUp::validate_password(){
    bool valid_size = true;
    bool valid_numbers = false;
    bool valid_upper = false;
    bool valid_lower = false;
    QString pass = password_edit->text();
    if (pass.size()<8){
        valid_size = false;
    }
    for (int i = 0 ; i<pass.size(); i++){
        if ( pass[i]>='0' and pass[i]<='9'){
            valid_numbers = true;
        }
        else if (pass[i]>='a' and pass[i]<='z'){
            valid_lower = true;
        }
        else if (pass[i]>='A' and pass[i]<='Z'){
            valid_upper = true;
        }

        if (valid_lower and valid_upper and valid_numbers){
            break;
        }
    }

    if ( (!valid_size) or (!valid_lower) or (!valid_upper) or (!valid_numbers) ){
        invalid(password, 2);
        return false;
    }

    return true;

}

/**
 * @brief signUp::login_instead, slot for user to go back to login screen
 * @file signup.h
 */
void signUp::login_instead(){
    login* log_window = new login();
    log_window->show();
    this->close();
}


/**
 * @brief signUp::upload_picture, user uploads profile pic
 * @file signup.h
 * lets user browse the computer to upload pic, if none chosen uploads a generic icon
 */
void signUp::upload_picture(){

    // filename variable will hold the name of the file the user chooses
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose a picture"),
                                                    "", tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    // check if file name is valid

    if(QString::compare(filename, QString()) != 0 ){

        QImage image;
        bool valid = image.load(filename);  // if what is loaded is a valid image it's true

        if (valid){

            image = image.scaledToWidth(browse_pic->width(), Qt::SmoothTransformation);
            browse_pic->setPixmap(QPixmap::fromImage(image));

        } else{
            // We can add some kind of error handling
        }

    }

}


/**
 * @brief signUp::invalid, creates invalid window
 * @param label
 * @param errorCode
 * @file signup.h
 * creates invalid window depending on which label and error code the user got
 */
void signUp::invalid(QLabel* label, int errorCode) {
    errorWindows* errW = new errorWindows();
    if (label->text()=="Username"){
        if(errorCode==1){
            errW->setErrorLabel("Username already taken!");
        }else if (errorCode==0){
            errW->setErrorLabel("Username field is empty!");
        } else if (errorCode==2){
            errW->setErrorLabel("Username should not contain a space!");
        }
        username_edit->setStyleSheet("border: 1px solid red;");
    } else if(label->text()=="First Name"){
        errW->setErrorLabel("First name field is empty!");
        firstName_edit->setStyleSheet("border: 1px solid red;");
    } else if(label->text()=="Last Name"){
        errW->setErrorLabel("Last Name field is empty!");
        lastName_edit->setStyleSheet("border: 1px solid red;");
    } else if(label->text()=="Gender"){
        errW->setErrorLabel("Gender field is empty!");
    } else if(label->text()=="Password"){
        if(errorCode==0){
            errW->setErrorLabel("Password field is empty!");
            password_edit->setStyleSheet("border: 1px solid red;");
        }
        else if (errorCode==1){
            errW->setErrorLabel("Password field and confirm password are not holding the same password!");
            confirm_edit->setStyleSheet("border: 1px solid red;");
        }
        else if(errorCode==2){
            errW->setErrorLabel("Password must contain at least 8 letters, one uppercase, one lowercase and a number!");
            password_edit->setStyleSheet("border: 1px solid red;");
        }
    }
    errW->show();
}


/**
 * @brief signUp::signup, signs up the user
 * @file signup.h
 */
void signUp::signup() {
    User user;
    if (QString::compare(username_edit->text(), QString()) == 0) {
        invalid(username, 0);
        return;
    } else if (QString::compare(firstName_edit->text(), QString()) == 0) {
        invalid(first_name, 0);
        return;
    } else if (QString::compare(lastName_edit->text(), QString()) == 0) {
        invalid(last_name, 0);
        return;
    } else if (QString::compare(password_edit->text(), QString()) == 0) {
        invalid(password, 0);
        return;
    } else if (QString::compare(confirm_edit->text(), QString()) == 0 ) {
        invalid(confirm_password,0);
        return;
    } else if (QString::compare(confirm_edit->text(), password_edit->text()) != 0){
        invalid(password, 1);
        return;
    } else if (!gender_male->isChecked() && !gender_female->isChecked() && !gender_other->isChecked()) {
        invalid(gender, 0);
        return;
    } else if (!validate_Username()){
        return;
    } else if (!validate_password()){
        return;
    }
    user.setUsername(username_edit->text());
    user.setPassword(password_edit->text());
    user.setFirstName(firstName_edit->text());
    user.setLastName(lastName_edit->text());
    user.setDateOfBirth(date_birth_calendar->selectedDate());
    user.setProfilePicture(*(browse_pic->pixmap()));
    if (gender_male->isChecked()) {
        user.setGender(User::Male);
    } else if (gender_female->isChecked()) {
        user.setGender(User::Female);
    } else {
        user.setGender(User::Other);
    }
    QVector<int> scores;
    for (int i=0; i<10; i++) {
        scores.append(i*100);
    }
    user.setScores(scores);
    app.signup(user);
    // display success window
    successWindow* sW = new successWindow();
    sW->setSuccessLabel("User successfully created! You can now head back to Log In!");
    sW->show();
    username_edit->setText("");
    password_edit->setText("");
    confirm_edit->setText("");
    firstName_edit->setText("");
    lastName_edit->setText("");

}

