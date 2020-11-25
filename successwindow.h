#ifndef SUCCESSWINDOW_H
#define SUCCESSWINDOW_H

#include <QWidget>
#include<QObject>
#include<QtWidgets>

class successWindow : public QWidget
{
    Q_OBJECT
public:
    explicit successWindow(QWidget *parent = nullptr);

signals:

private:
    QLabel* sucessLabel;
    QLabel* successMessage;

    QVBoxLayout* verticalLayout;

public :
    void setSuccessLabel(QString str);
    void setSuccessLabelPicture(QPixmap pic);
    void changeSuccessLabel(QString str);

};

#endif // SUCCESSWINDOW_H
