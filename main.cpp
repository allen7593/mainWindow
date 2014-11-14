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
//    //a.exec();
//    while(true)
//    {
//        switch(w->getStatus())
//        {
//            case 0:
//                a.exec();

//                break;
//            case 1:
//                w->hide();
//                delete w;
//                w=new MainWindow;
//                w->show();
//                w->setStyleSheet(stylesheet);
//                setCenterOfApplication(w);
//                w->setStatus(0);
//                break;
//            case 2:
//            return 0;
//                break;
//        }
//    }

    return a.exec();
}


