#include "playscene.h"
#include<QDebug>
#include<QMenu>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include"QPropertyAnimation"
#include<QSound>
PlayScene::PlayScene(int levelNum)
{
    QSound *backSound=new QSound(":/res/BackButtonSound.wav");
    QSound*flipSound=new QSound(":/res/CoinFlipSound.wav");
    QSound*winSound=new QSound(":/res/LevelWinSound.wav");
    //先加上音效
    QString str=QString("进入了 %1关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex=levelNum;
    //设置大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");
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
        //qDebug()<<"点击了button";
        //主场景监听返回按钮
        backSound->play();//先播放返回按钮音效
        QTimer::singleShot(300,this,[=](){
            emit this->chooseSceneBack();
        });
    });
    //显示关卡数
    QLabel *label=new QLabel;
    label->setParent(this);
    QString str1=QString("第 %1 关").arg(this->levelIndex);
    label->setText(str1);
    QFont qfont;
    qfont.setFamily("华文新魏");
    qfont.setPointSize(20);
    label->setFont(qfont);
    label->setGeometry(30,this->height()-50,120,50);

    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }
    //胜利图片显示
    QLabel*winlabel=new QLabel;
    QPixmap tmppix;
    bool suc=tmppix.load(":/res/LevelCompletedDialogBg.png");
    if(suc)qDebug()<<"success show 胜利图片";
    winlabel->setPixmap(tmppix);
    winlabel->setParent(this);
    winlabel->setGeometry(0,0,tmppix.width(),tmppix.height());
    winlabel->move(this->width()*0.5-tmppix.width()*0.5,-50);//还没有砸下来
    winlabel->hide();

    //显示金币背景图案
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            QPixmap pix=QPixmap(":/res/BoardNode(1).png");
            QLabel *label=new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+i*50,200+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j]==0)str=":/res/Coin0008.png";
            else str=":/res/Coin0001.png";
            MyCoin *coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            //给金币赋值
            coin->posX=i;
            coin->posy=j;
            coin->flag=this->gameArray[i][j];//1是正面，2是反面
            //将金币放入便于维护
            coinBtn[i][j]=coin;
            //点击金币进行翻转
            connect(coin,&MyCoin::clicked,[=](){//本质上coin也是widget所以可以clicked
                flipSound->play();
                coin->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;
                //翻转周围的金币,但是现在不能看到其他硬币
                if(coin->posX+1<=3){
                    coinBtn[coin->posX+1][coin->posy]->changeFlag();
                    this->gameArray[coin->posX+1][coin->posy]=this->gameArray[i][j]==0?1:0;
                }//侧周围的金币翻转条件
                if(coin->posy+1<=3){
                    coinBtn[coin->posX][coin->posy+1]->changeFlag();
                    this->gameArray[coin->posX][coin->posy+1]=this->gameArray[i][j]==0?1:0;
                }//侧周围的金币翻转条件
                if(coin->posX-1>=0){
                    coinBtn[coin->posX-1][coin->posy]->changeFlag();
                    this->gameArray[coin->posX-1][coin->posy]=this->gameArray[i][j]==0?1:0;
                }//侧周围的金币翻转条件
                if(coin->posy-1>=0){
                    coinBtn[coin->posX][coin->posy-1]->changeFlag();
                    this->gameArray[coin->posX][coin->posy-1]=this->gameArray[i][j]==0?1:0;
                }//侧周围的金币翻转条件
                //判断是否胜利
                this->isWin=true;
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){
                        if(coinBtn[i][j]->flag==false)this->isWin=false;
                    }
                }
                if(isWin){
                    winSound->play();
                    qDebug()<<"ISWIn";
                    //不能再操作了
                    for(int i=0;i<=3;i++){
                        for(int j=0;j<=3;j++){
                            coinBtn[i][j]->iswin=true;
                        }
                    }
                    //胜利图片显示
                    winlabel->show();
                    //胜利图片移动
                    QPropertyAnimation *animation=new QPropertyAnimation(winlabel,"geometry");
                    animation->setDuration(1000);
                    //设置开始位置
                    animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                    //设置结束位置
                    animation->setEndValue(QRect(winlabel->x(),winlabel->y()+114,winlabel->width(),winlabel->height()));
                    //设置缓和曲线
                    animation->setEasingCurve(QEasingCurve::OutBounce);
                    //执行动画
                    animation->start();
                }
            });
        }
    }
}
void PlayScene::paintEvent(QPaintEvent*){
    QPixmap BackGroundPic;
    BackGroundPic.load(":/res/PlayLevelSceneBg.png");
    BackGroundPic=BackGroundPic.scaled(BackGroundPic.width()*0.9,BackGroundPic.height()*0.9);
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),BackGroundPic);
};
