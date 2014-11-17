#ifndef PICGEN_H
#define PICGEN_H

#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <string>
#include <QCryptographicHash>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <sstream>
#include <QString>
#include <fstream>
#include "rangen.h"
#include "aes_ctr.h"

class picGen
{
public:
    picGen();
    ~picGen();

    void excu();
    void setKey(int);
    QImage* getShare1();
    QImage* getShare2();
    void mainPic();
    QString getHashedSecret();
    void loadShare1();

private:
    static const int width=60;
    static const int height=30;
    std::string secretStr;
    QImage* s1;
    QImage* s2;
    QImage* s1Ex;
    QImage* s2Ex;

    QImage* secret;
    QImage* picAli;

    QRgb black;
    QRgb white;

    ranGen *g;

    void share1Gen();
    void secretGen();

    void setToBlack(QImage*,int,int);
    void setToWhite(QImage*,int,int);

    void topHor(QImage*,int,int);
    void botHor(QImage*,int,int);
    void lefVer(QImage*,int,int);
    void rigVer(QImage*,int,int);
    void lefDia(QImage*,int,int);
    void rigDia(QImage*,int,int);

    void saveAll();

    void extendShare();
    void alignment();

    std::string homePath;

};


std::string generateRanStr();

#endif // PICGEN_H
