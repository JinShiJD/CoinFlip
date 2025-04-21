#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
public:
//    explicit MyPushButton(QWidget *parent = nullptr);

    //构造函数 参数1 正常显示的图片路径 参数2 按下后显示的图片路径
    MyPushButton(QString normalImg, QString pressImg = "");

    // 成员属性保存用户传入的默认显示路径 以及按下后显示的图片路径
    QString normalImagPath;
    QString pressImgPath;

    //弹跳特性
    void bounce1(); //向下跳
    void bounce2(); //向上跳

    //重写按钮 按下 和 释放事件
    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

signals:

};

#endif // MYPUSHBUTTON_H
