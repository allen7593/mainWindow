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



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint)
{
    count=5;
    p=new picGen;
    p->mainPic();
    //srand(100);
    pixLabel=new QLabel;
    QImage* image;
    //p->loadShare1();
    image=p->getShare2();
    QSize s(1000,500);

    pixLabel->setPixmap(QPixmap::fromImage(image->scaled(s,Qt::KeepAspectRatio,Qt::FastTransformation)));
    QWidget *centerWindow=new QWidget;
    this->setCentralWidget(centerWindow);

    varifyLabe=new QLabel(tr("Please enter the verification number."));
    varifyEdit=new QLineEdit;

    //varifyLabe->setBuddy(varifyEdit);

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
    mainLayout->addStretch();

    connect(varifyEdit,SIGNAL(textChanged(const QString&)),this,SLOT(enableButton(const QString&)));
    connect(varifyButton,SIGNAL(clicked()),this,SLOT(checkForCode()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(logoutBut,SIGNAL(clicked()),this,SLOT(logout()));

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

    QFont font;
    font.setPixelSize(50);

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
    //hPlaceHolder->addWidget(groupBox);

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

MainWindow::~MainWindow()
{
}

void MainWindow::enableButton(const QString& text)
{
    //varifyButton->setEnabled(!text.isEmpty());
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
            close();
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


void MainWindow::logout()
{
    QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this,tr("Warning"),tr("Do you really wants to logout?"),QMessageBox::Ok|QMessageBox::Cancel);
    if(reply==QMessageBox::Ok)
        system("kill -9 -1");
    else
        return;
}
