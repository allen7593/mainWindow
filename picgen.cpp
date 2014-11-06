#include "picgen.h"
#include <iostream>
std::string generateRanStr()
{
    std::srand(time(NULL));
    std::string secretStr;
    char temp;
    for(int i=0;i<5;i++)
    {
        secretStr=secretStr.substr(0,i);
        switch(std::rand()%2)
        {
            case 0:
                temp=(char)(std::rand()%10+48);
                secretStr.append(&temp);
                break;
            case 1:
                temp=(char)(std::rand()%26+97);
                secretStr.append(&temp);
                break;
        }
    }
    secretStr=secretStr.substr(0,5);
    return secretStr;
}


picGen::picGen()
{

    homePath="/home/allen7593";

    black=qRgba(0,0,0,255);
    white=qRgba(255,255,255,0);

    s1=new QImage(width*2,height*2,QImage::Format_RGBA8888);
    s2=new QImage(width*2,height*2,QImage::Format_RGBA8888);
    secret=new QImage(width,height,QImage::Format_RGBA8888);

    s1Ex=new QImage(width*6,height*6,QImage::Format_RGBA8888);
    s2Ex=new QImage(width*6,height*6,QImage::Format_RGBA8888);

    //setup a transparent pic for secret drawing
        for(int i=0;i<width;i++)
            for(int j=0;j<height;j++)
                secret->setPixel(i,j,white);

        //write words on the pic
        secretStr=generateRanStr();
        QPainter painter;
        QFont font;
        font.setPixelSize(15);
        //font.setBold(true);
        font.setStyleHint(QFont::TypeWriter);
        painter.begin(secret);
        painter.setFont(font);
        painter.drawText(0,15,secretStr.c_str());
        painter.end();

}


picGen::~picGen()
{
}

QString picGen::getHashedSecret()
{
    QString hashedVal;
    QByteArray bb(secretStr.c_str());
    hashedVal=QCryptographicHash::hash((bb),QCryptographicHash::Sha1).toHex();
    return hashedVal;
}

QImage* picGen::getShare1()
{
    return s1Ex;
}

QImage* picGen::getShare2()
{
    return picAli;
}

void picGen::loadShare1()
{
    std::string absPath=homePath+"/Overlapit/s1.png";

    s1->load(absPath.c_str());
}

void picGen::mainPic()
{
    loadShare1();
    secretGen();
    extendShare();
    alignment();
    //saveAll();

}

void picGen::excu()
{
    share1Gen();
    secretGen();

    extendShare();


    saveAll();
}

void picGen::setKey(int num)
{
    g=new ranGen;
    g->srand(num);
}

void picGen::share1Gen()
{
    int caseNum;
    for(int i=0;i<width*2;i+=2)
        for(int j=0;j<height*2;j+=2)
        {
            caseNum=abs(g->rand())%6;
            //std::cout<<caseNum<<std::endl;
            switch(caseNum)
            {
                case 0:
                    topHor(s1,i,j);
                    break;
                case 1:
                    botHor(s1,i,j);
                    break;
                case 2:
                    lefVer(s1,i,j);
                    break;
                case 3:
                    rigVer(s1,i,j);
                    break;
                case 4:
                    lefDia(s1,i,j);
                    break;
                case 5:
                    rigVer(s1,i,j);
            }
        }
}


void picGen::secretGen()
{
    for(int i=0;i<width;i++)
        for(int j=0;j<height;j++)
        {
            if(secret->pixel(i,j)!=white)
            {
                if(s1->pixel(i*2,j*2)==black && s1->pixel(i*2,j*2+1)==black)    //top
                    botHor(s2,i*2,j*2);
                else if(s1->pixel(i*2+1,j*2)==black && s1->pixel(i*2+1,j*2+1)==black)//bot
                    topHor(s2,i*2,j*2);
                else if(s1->pixel(i*2,j*2)==black && s1->pixel(i*2+1,j*2)==black)//left
                    rigVer(s2,i*2,j*2);
                else if(s1->pixel(i*2,j*2+1)==black && s1->pixel(i*2+1,j*2+1)==black)//right
                    lefVer(s2,i*2,j*2);
                else if(s1->pixel(i*2,j*2)==black && s1->pixel(i*2+1,j*2+1)==black)//left to right
                    rigDia(s2,i*2,j*2);
                else if(s1->pixel(i*2+1,j*2)==black && s1->pixel(i*2,j*2+1)==black)//right to left
                    lefDia(s2,i*2,j*2);
             }
             else
             {
                if(s1->pixel(i*2,j*2)==black && s1->pixel(i*2,j*2+1)==black)    //top
                    topHor(s2,i*2,j*2);
                else if(s1->pixel(i*2+1,j*2)==black && s1->pixel(i*2+1,j*2+1)==black)//bot
                    botHor(s2,i*2,j*2);
                else if(s1->pixel(i*2,j*2)==black && s1->pixel(i*2+1,j*2)==black)//left
                    lefVer(s2,i*2,j*2);
                else if(s1->pixel(i*2,j*2+1)==black && s1->pixel(i*2+1,j*2+1)==black)//right
                    rigVer(s2,i*2,j*2);
                else if(s1->pixel(i*2,j*2)==black && s1->pixel(i*2+1,j*2+1)==black)//left to right
                    lefDia(s2,i*2,j*2);
                else if(s1->pixel(i*2+1,j*2)==black && s1->pixel(i*2,j*2+1)==black)//right to left
                    rigDia(s2,i*2,j*2);
               }
        }
}


void picGen::topHor(QImage* pic,int i,int j)
{
    pic->setPixel(i,j,black);
    pic->setPixel(i,j+1,black);

    pic->setPixel(i+1,j,white);
    pic->setPixel(i+1,j+1,white);
}

void picGen::botHor(QImage* pic,int i,int j)
{
    pic->setPixel(i+1,j,black);
    pic->setPixel(i+1,j+1,black);

    pic->setPixel(i,j,white);
    pic->setPixel(i,j+1,white);

}
void picGen::lefVer(QImage* pic,int i,int j)
{
    pic->setPixel(i+1,j,black);
    pic->setPixel(i,j,black);

    pic->setPixel(i,j+1,white);
    pic->setPixel(i+1,j+1,white);

}

void picGen::rigVer(QImage* pic,int i,int j)
{
    pic->setPixel(i,j+1,black);
    pic->setPixel(i+1,j+1,black);

    pic->setPixel(i+1,j,white);
    pic->setPixel(i,j,white);
}


void picGen::lefDia(QImage* pic,int i,int j)
{
    pic->setPixel(i,j,black);
    pic->setPixel(i+1,j+1,black);

    pic->setPixel(i+1,j,white);
    pic->setPixel(i,j+1,white);
}

void picGen::rigDia(QImage* pic,int i,int j)
{
    pic->setPixel(i+1,j,black);
    pic->setPixel(i,j+1,black);

    pic->setPixel(i,j,white);
    pic->setPixel(i+1,j+1,white);
}


void picGen::setToBlack(QImage* pic,int i,int j)
{
    for(int k=i;k<i+3;k++)
        for(int l=j;l<j+3;l++)
            pic->setPixel(k,l,black);
}

void picGen::setToWhite(QImage* pic,int i,int j)
{
    for(int k=i;k<i+3;k++)
        for(int l=j;l<j+3;l++)
            pic->setPixel(k,l,white);
}

void picGen::extendShare()
{
    for(int i=0;i<width*2;i++)
        for(int j=0;j<height*2;j++)
        {
            if(s1->pixel(i,j)==black)
                setToBlack(s1Ex,i*3,j*3);
            else
                setToWhite(s1Ex,i*3,j*3);
            if(s2->pixel(i,j)==black)
                setToBlack(s2Ex,i*3,j*3);
            else
                setToWhite(s2Ex,i*3,j*3);
        }
}

void picGen::saveAll()
{
    s1->save("s1.png");
    s2->save("s2.png");

    alignment();
    QSize s(1000,500);
    *s1Ex=s1Ex->scaled(s,Qt::KeepAspectRatio,Qt::FastTransformation);
    *s2Ex=s2Ex->scaled(s,Qt::KeepAspectRatio,Qt::FastTransformation);
    s1Ex->save("s1Ex.png");
    s2Ex->save("s2Ex.png");
    //s2Ex->save("/home/allen7593/sharet.png");
    secret->save("secret.png");
}


void picGen::alignment()
{
    int size=9;
    picAli = new QImage(width*6+size*2,height*6+size*2,QImage::Format_RGBA8888);
    QRgb green,white;
    green = qRgba(0,255,0,255);
    white = qRgba(255,255,255,0);
    //set to transparent
    for(int i=0;i<width*6+size*2;i++)
        for(int j=0;j<height*6+size*2;j++)
            picAli->setPixel(i,j,white);
    for(int i=size-1;i<width*6+size-1;i++)
        for(int j=size-1;j<height*6+size-1;j++)
            picAli->setPixel(i,j,s2Ex->pixel(i-(size-1),j-(size-1)));


    //top left corner
    for(int i=0;i<size*2;i++)
        for(int j=0;j<size*2;j++)
            picAli->setPixel(i,j,green);

    //top Right corner
    for(int i=width*6-1;i<width*6+size*2-1;i++)
        for(int j=0;j<size*2;j++)
                picAli->setPixel(i,j,green);

    //bot left corner
    for(int i=0;i<size*2;i++)
        for(int j=height*6-1;j<height*6+size*2-1;j++)
            picAli->setPixel(i,j,green);

    //bot right corner
    for(int i=width*6-1;i<width*6+size*2-1;i++)
        for(int j=height*6-1;j<height*6+size*2-1;j++)
            picAli->setPixel(i,j,green);

    QSize s(1000,500);
    *picAli=picAli->scaled(s,Qt::KeepAspectRatio,Qt::FastTransformation);

    picAli->save("picAli.png");
}
