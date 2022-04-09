#include "mycoin.h"
#include<QDebug>
MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret){
        qDebug()<<QString("图片 %1 加载失败").arg(btnImg);
        return ;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    //初始化timer
    timer1=new QTimer(this);
    timer2=new QTimer(this);
    //将信号和翻金币连接
    connect(timer1,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str=QString(":/res/Coin000%1").arg(this->min++);
       pix.load(str);
       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px}");
       this->setIcon(pix);//相当于改变图标
       this->setIconSize(QSize(pix.width(),pix.height()));
       //翻完了重置为1
       if(this->min>this->max){
           this->min=1;
           timer1->stop();//计时器停下来

       }
    });
    //将信号和翻银币连接
    connect(timer2,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str=QString(":/res/Coin000%1").arg(this->max--);
       pix.load(str);
       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px}");
       this->setIcon(pix);//相当于改变图标
       this->setIconSize(QSize(pix.width(),pix.height()));
       //翻完了重置为1
       if(this->min>this->max){
           this->max=8;
           timer2->stop();//计时器停下来
       }
    });
}
//实现改变正反面的方法
void MyCoin::changeFlag(){
    //如果是正面翻反面
    if(this->flag){
        //开始计时
        timer1->start(30);

        this->flag=false;//已经翻转
        //需要写一个定时器连接
    }
    else {
        timer2->start(30);

        this->flag=1;//已经翻转
    }
};


void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->iswin){
        return ;//可以拦截操作
    }
    else {
        QPushButton::mousePressEvent(e);//不写这句全部拦截
    }
}
