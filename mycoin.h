#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include<QPushButton>
#include<QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //传入一个路径
    MyCoin(QString btnImg);

    //增加属性
    int posX;
    int posy;
    bool flag;
    //改变标志的方法
    void changeFlag();
    QTimer *timer1;//正面翻反面的定时器
    QTimer *timer2;
    int min=1;//用来记录翻那张图片的
    int max=8;
    bool iswin=false;//如果已经胜利，不要再可以点击
    void mousePressEvent(QMouseEvent *e);
signals:

};
#endif // MYCOIN_H
