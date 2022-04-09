#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>
#include<QMouseEvent>
//MypushButton::MypushButton(QWidget *parent) : QPushButton(parent)
//{

//}
MypushButton::MypushButton(QString normImage,QString PressImg){//函数申明和定义中只能有一个有默认参数
    this->normImagePath=normImage,this->PressImgPath=PressImg;//记录更改属性
    QPixmap pix;
    bool ret=pix.load(normImage);//加载用户的图
    if(!ret){
        qDebug()<<"图片加载失败";
    }
    this->setFixedSize(pix.width(),pix.height());//设置按钮大小
    this->setStyleSheet("QPushButton{border:0px;}");//设置不规则图片样式,去边缘
    this->setIcon(pix);//设置图标
    this->setIconSize(QSize(pix.width(),pix.height()));//设置让图片和按钮等大



};

void MypushButton::zoomdown(){
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);//设置动画间隔
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::InBounce);
    animation->start();
};
void MypushButton::zoomup(){
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);//设置动画间隔
    animation->setStartValue(QRect(this->x(),this->y()+1,this->width(),this->height()));
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::InBounce);
    animation->start();
};
void MypushButton::mousePressEvent(QMouseEvent *ev){
    if(this->PressImgPath!=""){
        //仅当按下图片不为空才需要切换
        QPixmap pix;
        bool ret=pix.load(this->PressImgPath);//加载用户的图
        if(!ret){
            qDebug()<<"图片加载失败";
        }
        this->setFixedSize(pix.width(),pix.height());//设置按钮大小
        this->setStyleSheet("QPushButton{border:0px;}");//设置不规则图片样式,去边缘
        this->setIcon(pix);//设置图标
        this->setIconSize(QSize(pix.width(),pix.height()));//设置让图片和按钮等大
        //让父类处理最后的内容
    }
    return QPushButton::mousePressEvent(ev);
};
void MypushButton::mouseReleaseEvent(QMouseEvent *ev){
    if(this->PressImgPath!=""){
        //仅当按下图片不为空才需要切换
        QPixmap pix;
        bool ret=pix.load(this->normImagePath);//加载用户的图
        if(!ret){
            qDebug()<<"图片加载失败";
        }
        this->setFixedSize(pix.width(),pix.height());//设置按钮大小
        this->setStyleSheet("QPushButton{border:0px;}");//设置不规则图片样式,去边缘
        this->setIcon(pix);//设置图标
        this->setIconSize(QSize(pix.width(),pix.height()));//设置让图片和按钮等大
        //让父类处理最后的内容
    }
    return QPushButton::mouseReleaseEvent(ev);
};
