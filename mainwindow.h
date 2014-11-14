#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <sstream>
#include <QTimer>
#include <QDateTime>
#include <QPalette>

#include "picgen.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void enableButton(const QString&);
    void checkForCode();
    void logout();
    void countDown();
private:
    QLabel *varifyLabe;
    QLabel *pixLabel;
    QLineEdit *varifyEdit;
    QPushButton *varifyButton;
    QPushButton *closeButton;

    QPushButton* logoutBut;
    QLabel* timeLabel;
    QLabel* timeWarning;
    QTime time;

    int count;
    int timeCount;

    picGen* p;
};

#endif // MAINWINDOW_H
