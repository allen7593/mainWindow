#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QPushButton *button5;
    QVBoxLayout *layout;
};

#endif // MAINWINDOW_H
