// POINTER STAR (*) POSITION:
/*
 * star next to type better explains the sentence "obj is of type
 * Pointer to QObject" since the star is associated with the type,
 * not the variable name.
 *
 * However, initializing several pointer variables on the same line
 * is not consistent with that behavior since, in the example below,
 * obj1's type will be QObject* while that of obj2 would be QObject,
 * which is why we should refrain from using same line initializations.
 *
 * */
QObject* obj = new QObject();

//Do:
QObject* obj1;
QObject* obj2;

//Don't:
QObject* obj1, obj2; //not same behavior!!



//VARIABLE NAMING:
/*name should start with specific purpose of object followed by exact
 * name of QObject.
 * */
QPushButton* signUpPushButton;
QLineEdit* usernameLineEdit;
QLabel* passwordLabel;
//...



//BRACES:
/* Same for all kinds (class, for, function etc.) */
class A: public B {
	
};
