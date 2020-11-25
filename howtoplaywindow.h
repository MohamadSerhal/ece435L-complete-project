#ifndef HOWTOPLAYWINDOW_H
#define HOWTOPLAYWINDOW_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

class howToPlayWindow : public QWidget
{
    Q_OBJECT
public:
    explicit howToPlayWindow(QWidget *parent = nullptr);

private:
    void centerWindow();
    void setupBackground();
    void setupWidgets();
    void setupLayout();

    QVBoxLayout* verticalLayout;
    QLabel* explainLabel;
    QLabel* titleLabel;
signals:

};

#endif // HOWTOPLAYWINDOW_H
