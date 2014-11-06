#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QWidget *centerWindow = new QWidget;
        this->setCentralWidget(centerWindow);

        button1 = new QPushButton("One");
        button2 = new QPushButton("Two");
        button3 = new QPushButton("Three");
        button4 = new QPushButton("Four");
        button5 = new QPushButton("Five");
        layout = new QVBoxLayout;
        layout->addWidget(button1);
        layout->addWidget(button2);
        layout->addWidget(button3);
        layout->addWidget(button4);
        layout->addWidget(button5);
        QGroupBox *groupBox = new QGroupBox(tr("登录"));
        groupBox->setLayout(layout);
        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(groupBox);

        centerWindow->setLayout(mainLayout);
    //ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
