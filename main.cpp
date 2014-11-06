#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QTextStream>
void setCenterOfApplication(QMainWindow* widget);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //w.showFullScreen();

    QFile file("stylesheet.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet=filetext.readAll();

    w.setStyleSheet(stylesheet);


    setCenterOfApplication(&w);

    return a.exec();
}


void setCenterOfApplication(QMainWindow* widget)
{
    QSize size = widget->sizeHint();
    QDesktopWidget* desktop = QApplication::desktop();
    int width = desktop->width();
    int height = desktop->height();
    int mw = size.width();
    int mh = size.height();
    int centerW = (width/2) - (mw/2);
    int centerH = (height/2) - (mh/2);
    widget->move(centerW, centerH);
}

