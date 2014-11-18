#ifndef RECDIA_H
#define RECDIA_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <unistd.h>
#include <fstream>
#include "aes_ctr.h"

class recDia : public QDialog
{
    Q_OBJECT

public:
    recDia(QMainWindow *parent = 0);
    ~recDia();

private slots:
    void backToPrePage();
    void enableRec(const QString&);
    void recovery();

private:
    QLabel* nameLabel;
    QLabel* infoLabel;

    QLineEdit* recoveyEdit;

    QPushButton* recoveyBut;
    QPushButton* previousBut;
    QMainWindow* preWin;

    QString masterKey;
    QMessageBox mBox;

};

#endif // RECDIA_H
