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

#include <unistd.h>
#include "picgen.h"
#include "recdia.h"


void setCenterOfApplication(QMainWindow* widget);

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
    void refresh();
    void reset();
private:
    void construct();
    QLabel *varifyLabe;
    QLabel *pixLabel;
    QLineEdit *varifyEdit;
    QPushButton *varifyButton;
    QPushButton *closeButton;
    QPushButton *recBut;
    QPushButton* refreshBut;
    QPushButton* logoutBut;
    //QPushButton* recBut;
    QLabel* timeLabel;
    QLabel* timeWarning;
    QTime time;

    int count;
    int timeCount;
    int refreshVel;

    QTimer *timer;
    picGen* p;
};

#endif // MAINWINDOW_H
