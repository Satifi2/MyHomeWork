#include "mainscene.h"
#include "ui_mainscene.h"
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QSound>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    setFixedSize(320,588);//配置主场景
    setWindowIcon(QIcon(":/res/Coin0001.png"));//设置固定大小
    setWindowTitle("翻金币");//设置主场景名称
    QSound *startsound=new QSound(":/res/TapButtonSound.wav");//开始按钮音效
    connect(ui->actionleave,&QAction::triggered,this,[this](){
       this->close();
    });//退出按钮
    MypushButton*startBtn=new MypushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->width()*0.5);
    chooseScence=new ChooseLevelScene;
    connect(chooseScence,&ChooseLevelScene::chooseSceneBack,this,[=](){
       chooseScence->hide();
        this->show();
    });//返回设置
    connect(startBtn,&QPushButton::clicked,this,[=](){
        startsound->play();//点击发声
        qDebug()<<"点击成功";
        startBtn->zoomdown();
        //startBtn->zoomup();
        //进入到选择场景
        QTimer::singleShot(500,this,[=](){
            chooseScence->show();
            this->hide();//隐藏主场景
            //监听返回信号
        });//延时进入
    });
}
void MainScene::paintEvent(QPaintEvent *){
    QPixmap BackGroundPic;
    BackGroundPic.load(":/res/PlayLevelSceneBg.png");
    BackGroundPic=BackGroundPic.scaled(BackGroundPic.width()*0.9,BackGroundPic.height()*0.9);
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),BackGroundPic);



};
MainScene::~MainScene()
{
    delete ui;
}

