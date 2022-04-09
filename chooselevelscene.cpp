#include "chooselevelscene.h"
#include<QMenuBar>
#include<QDebug>
#include<QLabel>
#include<QTimer>
#include<bits/stdc++.h>
#include<QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡场景");
    QSound *choosesound=new QSound(":/res/TapButtonSound.wav");//开始按钮音效
    QSound *backSound=new QSound(":/res/TapButtonSound.wav");
    QMenuBar *bar=menuBar();

    setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitAction=startMenu->addAction("退出");
    //实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    MypushButton *backBtn=new MypushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&QPushButton::clicked,[=](){
        //先放音乐
        backSound->play();
        //qDebug()<<"点击了button";
        //主场景监听返回按钮
        QTimer::singleShot(300,this,[=](){
            emit this->chooseSceneBack();
        });
    });
    //创建选择关卡按钮
    for(int i=0;i<20;i++){
        MypushButton *menuBtn=new MypushButton(":res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4*70,130+i/4*70);
        qDebug()<<i<<endl;
        connect(menuBtn,&MypushButton::clicked,[=](){//原来是这里必须要拷贝构造，不然i消亡了
           choosesound->play();//先放音效
           QString str=QString("您选择了第 %1 关").arg(i);
           qDebug()<<str;// 为什么这个i就是有问题？
           play=new PlayScene(i+1);
           play->show();
           this->hide();
           connect(play,&PlayScene::chooseSceneBack,[&](){
               this->show();
               delete play;
               play=NULL;
           });
        });
        //默认点到的不是下面的，所以鼠标点不到
        QLabel*label=new QLabel;
        label->setParent(this);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignHCenter);
        label->setFixedSize(menuBtn->width(),menuBtn->height());//设置对齐
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,145+i/4*70);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}



void ChooseLevelScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
};
