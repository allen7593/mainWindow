#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QGroupBox>
#include <QImage>
#include <QPixmap>
#include <cstdlib>
#include <QProcess>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <unistd.h>
#include <QApplication>
#include <QDesktopWidget>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint)
{
    construct();

}

MainWindow::~MainWindow()
{
}

void MainWindow::construct()
{
    refreshVel=0;
    count=5;
    p=new picGen;
    p->mainPic();
    pixLabel=new QLabel;
    QImage* image;
    image=p->getShare2();
    QSize s(1000,500);

    pixLabel->setPixmap(QPixmap::fromImage(image->scaled(s,Qt::KeepAspectRatio,Qt::FastTransformation)));
    QWidget *centerWindow=new QWidget;
    this->setCentralWidget(centerWindow);

    time = QTime(0,1,30);
    QTimer *timer=new QTimer(this);
    timer->setInterval(1000);
    timeCount=1000;
    QFont font;
    font.setPixelSize(20);



    timeLabel=new QLabel();
    timeWarning=new QLabel();
    timeLabel->setFont(font);
    timeWarning->setFont(font);
    timeWarning->setStyleSheet("color:red");

    varifyLabe=new QLabel(tr("Please enter the verification number."));
    varifyEdit=new QLineEdit;

    varifyButton=new QPushButton(tr("&Verify"));
    closeButton=new QPushButton(tr("Close"));
    logoutBut=new QPushButton(tr("Logout"));

    varifyButton->setDisabled(true);

    QHBoxLayout *botLayout=new QHBoxLayout;
    botLayout->addStretch();
    botLayout->addWidget(varifyButton);
    botLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addWidget(varifyLabe);
    mainLayout->addWidget(varifyEdit);
    mainLayout->addLayout(botLayout);
    mainLayout->addWidget(logoutBut);
    mainLayout->addWidget(timeLabel);
    mainLayout->addWidget(timeWarning);
    mainLayout->addStretch();

    connect(varifyEdit,SIGNAL(textChanged(const QString&)),this,SLOT(enableButton(const QString&)));
    connect(varifyButton,SIGNAL(clicked()),this,SLOT(checkForCode()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(logoutBut,SIGNAL(clicked()),this,SLOT(logout()));
    connect(timer,SIGNAL(timeout()),this,SLOT(countDown()));
    timer->start();

    QGroupBox *groupBox = new QGroupBox(tr("Login"));
    groupBox->setLayout(mainLayout);

    QVBoxLayout *placeHolder = new QVBoxLayout;
    QHBoxLayout *hPlaceHolder=new QHBoxLayout;
    QVBoxLayout *rightLayout=new QVBoxLayout;

    QImage* logoImg=new QImage(987,414,QImage::Format_RGBA8888);
    logoImg->load("logo.png");
    QSize size(300,150);



    QLabel *LogoLaybel=new QLabel;

    LogoLaybel->setPixmap(QPixmap::fromImage(logoImg->scaled(size,Qt::KeepAspectRatio,Qt::FastTransformation)));



    LogoLaybel->setFont(font);
    LogoLaybel->setMinimumHeight(30);
    LogoLaybel->setMinimumWidth(200);

    rightLayout->addStretch();
    rightLayout->addWidget(LogoLaybel);
    rightLayout->addStretch();
    rightLayout->addWidget(groupBox);
    rightLayout->addStretch();

    hPlaceHolder->addWidget(pixLabel);
    hPlaceHolder->addLayout(rightLayout);

    placeHolder->addStretch();
    placeHolder->addLayout(hPlaceHolder);
    placeHolder->addStretch();

    QHBoxLayout* paddingHL=new QHBoxLayout;
    QVBoxLayout* paddingVL=new QVBoxLayout;

    paddingHL->addStretch();
    paddingHL->addLayout(placeHolder);
    paddingHL->addStretch();

    paddingVL->addStretch();
    paddingVL->addLayout(paddingHL);
    paddingVL->addStretch();

    centerWindow->setLayout(paddingVL);

    setMinimumWidth(1300);
    setMinimumHeight(560);

    setWindowFlags( ( (this->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint) );

}

void MainWindow::enableButton(const QString& text)
{
    varifyButton->setDisabled(text.isEmpty());
}

void MainWindow::checkForCode()
{

    QString hashedVal;
    QByteArray bb(varifyEdit->text().toStdString().c_str());
    hashedVal=QCryptographicHash::hash((bb),QCryptographicHash::Sha1).toHex();

    QString varCode = p->getHashedSecret();


    if(count>0)
        if(varCode==hashedVal)
        {
            refreshVel=2;
            close();
        }
        else
        {
            count--;
            std::string warningMsg;
            std::ostringstream oss;
            oss<<count;
            warningMsg.append("Wrong verify code\n");
            warningMsg.append(oss.str());
            warningMsg.append(" times left!");
            QMessageBox::warning(this, tr("Warning"),tr(warningMsg.c_str()),QMessageBox::Ok);

        }
    else
    {
        QMessageBox::warning(this, tr("Warning"),tr("Please logout the system, no more try is avaliable."),QMessageBox::Ok);
    }

}


void MainWindow::countDown()
{

    QString time_Display;


    time_Display=time.toString("hh:mm:ss");
    timeLabel->setText(time_Display);
    if(time.minute()==1 && time.second()==0)
        timeWarning->setText(tr("You have 1 minute left"));
    else if(time.minute()==0 && time.second()==30)
        timeWarning->setText(tr("You have 30 seconds left"));
    else if(time.minute()==0 && time.second()==0)
    {
        QMessageBox::StandardButton retvel;
        retvel=QMessageBox::warning(this,tr("Time out"),tr("You have no time left press Ok to refresh the page!"),QMessageBox::Ok);
        if(retvel==QMessageBox::Ok)
        {
            //do something
            refreshVel=1;
            this->close();
            QFile file("stylesheet.qss");
            file.open(QFile::ReadOnly);
            QTextStream filetext(&file);
            QString stylesheet=filetext.readAll();
            MainWindow *newWindow;
            newWindow=new MainWindow;
            newWindow->setStyleSheet(stylesheet);
            setCenterOfApplication(newWindow);
            newWindow->show();
        }
    }
    time=time.addSecs(-1);
}


void MainWindow::logout()
{
    QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this,tr("Warning"),tr("Do you really wants to logout?"),QMessageBox::Ok|QMessageBox::Cancel);
    if(reply==QMessageBox::Ok)
        system("kill -9 -1");
    else
        return;
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
