#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <Qstack>
#include <QPropertyAnimation>

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
    //?
    Ui::MainWindow *ui;
    QLabel *label[100];
    QLabel *gradel;
    //variable
    int value[100];
    struct pplace{int x,y;}place[100];
    int click,xy[2][2];
    int grade;
    //function
    void mousePressEvent(QMouseEvent *event);
    int randsetnum();
    int setpic();
    int clear();
    int check();
    int drop();
    int s(int);
    int showg();
};

#endif // MAINWINDOW_H
