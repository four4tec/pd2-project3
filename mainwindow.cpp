#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QLabel>
#include <QWidget>
#include <QPicture>
#include <QPushButton>
#include <QFocusEvent>
#include <cmath>
#include <iostream>
#include <ctime>
#include <QFont>
#include <unistd.h>
#include <QPropertyAnimation>
#include <QRect>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QMouseEvent>
#define max(x,y) (x>y?x:y)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui
    ui->setupUi(this);
    setWindowTitle("? demo - by four4tec");
    setFixedSize(450,650);
    //setObjectName("MainWindow");
    //setStyleSheet("#MainWindow{border-image:url(:/pics/num/back.jpg);}");
    //variable
    memset(value,0,sizeof(value));
    for(int i=0;i<100;i++){
        place[i].x=25+i%10*40;
        place[i].y=25+i/10*40;
    }
    click=0;
    grade=0;
    memset(xy,0,sizeof(xy));
    //?
    gradel=new QLabel(centralWidget());
    gradel->setText("Grade : 0");
    gradel->setGeometry(25,450,200,50);
    //label 10*10
    for(int i=0;i<100;i++){
        label[i]=new QLabel(centralWidget());
        label[i]->setScaledContents(1);
        label[i]->setGeometry(place[i].x,place[i].y,40,40);
        label[i]->show();
    }
    //?
    srand(time(NULL));
    randsetnum();
    if(check()){
        drop();
        while(check()){drop();}
    }
    setpic();
    grade=0;
}
MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::setpic(){
    for(int i=0;i<100;i++){
        //QString str=QString::number(value[i]);
        //label[i]->setPixmap(":pics/num/"+str+".jpg");
        int x=value[i]%5;
        if(value[i]==5){x=5;}
        QString str=QString::number(x);
        QString ss;
        if(value[i]/5==0){ss="";}
        if(value[i]/5==1 && x!=5){ss="^";}
        if(value[i]/5==2){ss=">";}
        if(value[i]/5==3){ss="#";}
        label[i]->setText("  "+str+ss);
    }
    return 0;
}
int MainWindow::randsetnum(){
    for(int i=0;i<100;i++){
        value[i]=rand()%4+1;
    }
    return 0;
}
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->x()<25 || event->x()>=425 || event->y()<=25 || event->y()>=425){return;}
    if(click==0){
        xy[click][0]=event->x();
        xy[click][1]=event->y();
        click++;
    }
    else if(click==1){
        xy[click][0]=event->x();
        xy[click][1]=event->y();
        click++;
        clear();
    }
    showg();
}
int MainWindow::clear(){
    int x1=(xy[0][0]-25)/40,y1=(xy[0][1]-25)/40;
    int x2=(xy[1][0]-25)/40,y2=(xy[1][1]-25)/40;
    if(!((abs(x1-x2)==1 && abs(y1-y2)==0) || (abs(x1-x2)==0 && abs(y1-y2)==1))){click=0;return 1;}
    value[x1+y1*10]^=value[x2+y2*10];value[x2+y2*10]^=value[x1+y1*10];value[x1+y1*10]^=value[x2+y2*10];
    if(check()){
        drop();
        while(check()){drop();}
    }
    else{
       // value[x1+y1*10]^=value[x2+y2*10];value[x2+y2*10]^=value[x1+y1*10];value[x1+y1*10]^=value[x2+y2*10];return 0;
    }
    setpic();
    click=0;
    return 0;
}
int MainWindow::check(){
    int cl=0;
    for(int i=0;i<10;i++){for(int j=0;j<6;j++){
        if(value[i+j*10]%5!=0&&value[i+j*10]%5==value[i+j*10+10]%5&&value[i+j*10]%5==value[i+j*10+20]%5&&value[i+j*10]%5==value[i+j*10+30]%5&&value[i+j*10]%5==value[i+j*10+40]%5){
            s(i+j*10);s(i+j*10+10);s(i+j*10+30);s(i+j*10+40);value[i+j*10+20]=5;cl++;
        }
    }}
    for(int i=0;i<6;i++){for(int j=0;j<10;j++){
        if(value[i+j*10]%5!=0&&value[i+j*10]%5==value[i+j*10+1]%5&&value[i+j*10]%5==value[i+j*10+2]%5&&value[i+j*10]%5==value[i+j*10+3]%5&&value[i+j*10]%5==value[i+j*10+4]%5){
            s(i+j*10);s(i+j*10+1);s(i+j*10+3);s(i+j*10+4);value[i+j*10+2]=5;cl++;
        }
    }}
    for(int i=0;i<8;i++){for(int j=0;j<8;j++){
        if(value[i+j*10]%5!=0&&value[i+j*10]%5==value[i+j*10+10]%5&&value[i+j*10]%5==value[i+j*10+20]%5&&value[i+j*10]%5==value[i+j*10+1]%5&&value[i+j*10]%5==value[i+j*10+2]%5){
            value[i+j*10]=value[i+j*10+10]%5+15;value[i+j*10+10]=0;value[i+j*10+20]=0;value[i+j*10+1]=0;value[i+j*10+2]=0;cl++;
        }
        if(value[i+j*10]%5!=0&&value[i+j*10]%5==value[i+j*10+1]%5&&value[i+j*10]%5==value[i+j*10+2]%5&&value[i+j*10]%5==value[i+j*10+12]%5&&value[i+j*10]%5==value[i+j*10+22]%5){
            value[i+j*10+2]=value[i+j*10+1]%5+15;value[i+j*10+1]=0;value[i+j*10]=0;value[i+j*10+12]=0;value[i+j*10+22]=0;cl++;
        }
        if(value[i+j*10]%5!=0&&value[i+j*10]%5==value[i+j*10+10]%5&&value[i+j*10]%5==value[i+j*10+20]%5&&value[i+j*10]%5==value[i+j*10+21]%5&&value[i+j*10]%5==value[i+j*10+22]%5){
            value[i+j*10+20]=value[i+j*10+10]%5+15;value[i+j*10+10]=0;value[i+j*10]=0;value[i+j*10+21]=0;value[i+j*10+22]=0;cl++;
        }
        if(value[i+j*10+2]%5!=0&&value[i+j*10+2]%5==value[i+j*10+12]%5&&value[i+j*10+2]%5==value[i+j*10+22]%5&&value[i+j*10+2]%5==value[i+j*10+21]%5&&value[i+j*10+2]%5==value[i+j*10+20]%5){
            value[i+j*10+22]=value[i+j*10+20]%5+15;value[i+j*10+21]=0;value[i+j*10+20]=0;value[i+j*10+12]=0;value[i+j*10+2]=0;cl++;
        }
        if(value[i+j*10+1]%5!=0&&value[i+j*10+1]%5==value[i+j*10+10]%5&&value[i+j*10+1]%5==value[i+j*10+11]%5&&value[i+j*10+1]%5==value[i+j*10+21]%5&&value[i+j*10+1]%5==value[i+j*10+12]%5){
            value[i+j*10+11]=value[i+j*10+10]%5+15;value[i+j*10+10]=0;value[i+j*10+1]=0;value[i+j*10+21]=0;value[i+j*10+12]=0;cl++;
        }
        if(value[i+j*10]%5!=0&&value[i+j*10]%5==value[i+j*10+10]%5&&value[i+j*10]%5==value[i+j*10+20]%5&&value[i+j*10]%5==value[i+j*10+11]%5&&value[i+j*10]%5==value[i+j*10+12]%5){
            value[i+j*10+10]=value[i+j*10]%5+15;value[i+j*10]=0;value[i+j*10+20]=0;value[i+j*10+11]=0;value[i+j*10+12]=0;cl++;
        }
        if(value[i+j*10]%5!=0&&value[i+j*10]%5==value[i+j*10+1]%5&&value[i+j*10]%5==value[i+j*10+2]%5&&value[i+j*10]%5==value[i+j*10+11]%5&&value[i+j*10]%5==value[i+j*10+21]%5){
            value[i+j*10+1]=value[i+j*10]%5+15;value[i+j*10]=0;value[i+j*10+2]=0;value[i+j*10+11]=0;value[i+j*10+21]=0;cl++;
        }
        if(value[i+j*10+21]%5!=0&&value[i+j*10+21]%5==value[i+j*10+20]%5&&value[i+j*10+21]%5==value[i+j*10+20]%5&&value[i+j*10+21]%5==value[i+j*10+11]%5&&value[i+j*10+21]%5==value[i+j*10+1]%5){
            value[i+j*10+21]=value[i+j*10+20]%5+15;value[i+j*10+20]=0;value[i+j*10+22]=0;value[i+j*10+11]=0;value[i+j*10+1]=0;cl++;
        }
        if(value[i+j*10+12]%5!=0&&value[i+j*10+12]%5==value[i+j*10+2]%5&&value[i+j*10+12]%5==value[i+j*10+22]%5&&value[i+j*10+12]%5==value[i+j*10+11]%5&&value[i+j*10+12]%5==value[i+j*10+10]%5){
            value[i+j*10+12]=value[i+j*10+2]%5+15;value[i+j*10+2]=0;value[i+j*10+22]=0;value[i+j*10+11]=0;value[i+j*10+10]=0;cl++;
        }
    }}
    for(int i=0;i<10;i++){for(int j=0;j<7;j++){
        if(value[i+j*10]%5!=0&&value[i+j*10]%5==value[i+j*10+10]%5&&value[i+j*10]%5==value[i+j*10+20]%5&&value[i+j*10]%5==value[i+j*10+30]%5){
            s(i+j*10);s(i+j*10+20);s(i+j*10+30);value[i+j*10+10]=value[i+j*10+10]%5+10;cl++;
        }
    }}
    for(int i=0;i<7;i++){for(int j=0;j<10;j++){
        if(value[i+j*10]%5!=0&&value[i+j*10]%5==value[i+j*10+1]%5&&value[i+j*10]%5==value[i+j*10+2]%5&&value[i+j*10]%5==value[i+j*10+3]%5){
            s(i+j*10);s(i+j*10+2);s(i+j*10+3);value[i+j*10+1]=value[i+j*10+1]%5+5;cl++;
        }
    }}
    for(int i=0;i<10;i++){for(int j=0;j<8;j++){
        if(value[i+j*10]%5!=0&&value[i+j*10]%5==value[i+j*10+10]%5&&value[i+j*10]%5==value[i+j*10+20]%5){
            s(i+j*10);s(i+j*10+10);s(i+j*10+20);cl++;
        }
    }}
    for(int i=0;i<8;i++){for(int j=0;j<10;j++){
        if(value[i+j*10]%5!=0&&value[i+j*10]%5==value[i+j*10+1]%5&&value[i+j*10]%5==value[i+j*10+2]%5){
            s(i+j*10);s(i+j*10+1);s(i+j*10+2);cl++;
        }
    }}
    return cl;
}
int MainWindow::drop(){
    for(int i=0;i<10;i++){for(int j=0;j<10;j++){
        if(value[i+j*10]==0){
            for(int k=j;k>=1;k--){
                value[i+k*10]^=value[i+k*10-10];value[i+k*10-10]^=value[i+k*10];value[i+k*10]^=value[i+k*10-10];
            }
        }
    }}
    for(int i=0;i<100;i++){
        if(value[i]==0){value[i]=rand()%4+1;}
    }
    return 0;
}
int MainWindow::s(int xy){
    int a,i,j,k,cases=value[xy]/5;
    if(value[xy]==5){cases=5;}
    else if(value[xy]==10){cases=0;}
    switch(cases){
    case 0:break;
    case 1:
        value[xy]=0;
        for(i=0;i<10;i++){
            s(xy%10+10*i);
        }
        break;
    case 2:
        value[xy]=0;
        for(i=0;i<10;i++){
            s(xy/10*10+i);
        }
        break;
    case 3:
        for(i=1;i>=0;i--){
            value[xy]=10*i;
            for(j=max(xy/10-1,0);j<=max(xy/10+1,9);j++){
                for(k=max(xy%10-1,0);k<=max(xy%10+1,10);k++){
                    s(10*j+i);
                }
            }
            if(check()){
                drop();
                while(check()){drop();}
            }
        }
        break;
    case 5:
        a=rand()%4+1;
        for(i=0;i<100;i++){
            if(value[i]%5==a){s(i);}
        }
        break;
    default:
        break;
    }
    if(value[xy]!=0){value[xy]=0;grade++;}
    return 0;
}
int MainWindow::showg(){
    QString str=QString::number(grade);
    gradel->setText("Grade : "+str);
    return 0;
}
