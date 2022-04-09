#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include<QPushButton>
class MypushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MypushButton(QWidget *parent = nullptr);
MypushButton(QString normImage,QString PressImg="");
QString normImagePath,PressImgPath;//保存按下前路径和按下后路径，让图片动起来
void zoomup();
void zoomdown();
void mousePressEvent(QMouseEvent *);
void mouseReleaseEvent(QMouseEvent *);
signals:

};

#endif // MYPUSHBUTTON_H
