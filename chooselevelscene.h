#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QWidget>
#include<QPainter>
#include<mypushbutton.h>
#include<playscene.h>
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    //游戏场景对象指针
    PlayScene *play=NULL;
signals:
    //写一个信号让主场景返回
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
