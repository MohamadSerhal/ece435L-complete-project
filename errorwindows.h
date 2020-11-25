#ifndef ERRORWINDOWS_H
#define ERRORWINDOWS_H

#include <QWidget>
#include<QObject>
#include<QtWidgets>

class errorWindows : public QWidget
{
    Q_OBJECT
public:
    explicit errorWindows(QWidget *parent = nullptr);
    int errorCount;

private:
    QLabel* errorTitle;
    QLabel* errorMessage;

    QVBoxLayout* verticalLayout;

signals:


public slots:
    void setErrorLabel(QString error);
};

#endif // ERRORWINDOWS_H
