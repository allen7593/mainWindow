#include "recdia.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

recDia::recDia(QMainWindow *parent)
    : QDialog(parent,Qt::FramelessWindowHint)
{



    preWin=parent;
    //preWin->hide();
    nameLabel = new QLabel(tr("Recovery"));
    infoLabel = new QLabel(tr("Input the master code to reset the program."));

    recoveyEdit = new QLineEdit();

    recoveyBut = new QPushButton(tr("&Recovery"));
    recoveyBut->setDisabled(true);
    previousBut = new QPushButton(tr("Previous"));

    infoLabel->setBuddy(recoveyEdit);

    QHBoxLayout* buttonLayout=new QHBoxLayout;
    QHBoxLayout* nameLayout=new QHBoxLayout;
    QVBoxLayout* mainLayout=new QVBoxLayout;


    connect(previousBut,SIGNAL(clicked()),this,SLOT(backToPrePage()));
    connect(recoveyEdit,SIGNAL(textChanged(const QString&)),this,SLOT(enableRec(const QString&)));
    connect(recoveyBut,SIGNAL(clicked()),this,SLOT(recovery()));

    nameLayout->addStretch();
    nameLayout->addWidget(nameLabel);
    nameLayout->addStretch();

    buttonLayout->addStretch();
    //buttonLayout->addWidget(previousBut);
    buttonLayout->addWidget(recoveyBut);

    mainLayout->addLayout(nameLayout);
    mainLayout->addWidget(infoLabel);
    mainLayout->addWidget(recoveyEdit);
    mainLayout->addLayout(buttonLayout);

    this->setLayout(mainLayout);
    setWindowFlags( ( (this->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint) );

    mBox.setText(tr("Wrong master key!"));
    mBox.setStandardButtons(QMessageBox::Cancel);
    mBox.setWindowFlags( ( (mBox.windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint) );
}

recDia::~recDia()
{
}

void recDia::backToPrePage()
{
    this->hide();
    preWin->show();

}

void recDia::enableRec(const QString & text)
{
    recoveyBut->setDisabled(text.isEmpty());
}

void recDia::recovery()
{
    if (0==access("assetmc", 0))
    {

//        QFile file("assetmc");
//        if (!file.open(QIODevice::ReadOnly | QIODevice::Truncate)) {
//            // error processing here
//            QMessageBox::warning(this, tr("Warning"),tr("File Reading error"),QMessageBox::Ok);
//            return;

//        }
//        QTextStream ts(&file);
//        masterKey =ts.readAll();

        string aesKey = "b7bd865cb99216307a49b2a6a7a66efd"; //128 bits key
        string aesIV = "ABCDEF0123456789";//128 bits
        string cipherText,plainText;

        ifstream file("assetmc");
        file>>cipherText;
        plainText=CTR_AESDecryptStr(aesKey, aesIV, cipherText.c_str());

        if(recoveyEdit->text().toStdString()==plainText)
        {
            file.close();
            //clear the system
            remove("assetmc");
            remove("asset1");
            remove("assetT");
            remove("off");
            remove("on");
            //system("rm assetmc asset1");
            QMessageBox::StandardButton rel;
            rel=QMessageBox::information(this, tr("Note!"),tr("Program restore sucessed\nPlease register again"),QMessageBox::Ok);
            if(rel==QMessageBox::Ok)
                exit(0);
        }
        else
        {
              QMessageBox::warning(this, tr("Warning"),tr("Invalid Master key"),QMessageBox::Ok);
        }


    }
    else
    {
        QMessageBox::warning(this, tr("Warning"),tr("No account exist"),QMessageBox::Ok);
        return;
    }


}
