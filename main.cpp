#include "mainwindow.h"
#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QTextStream>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w=new MainWindow;


    QFile file("stylesheet.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet=filetext.readAll();

    w->setStyleSheet(stylesheet);
    setCenterOfApplication(w);
    w->show();

    return a.exec();
}


