#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <sstream>
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
private:
    QLabel *varifyLabe;
    QLabel *pixLabel;
    QLineEdit *varifyEdit;
    QPushButton *varifyButton;
    QPushButton *closeButton;

    QPushButton* logoutBut;

    int count;

    picGen* p;
};

#endif // MAINWINDOW_H
