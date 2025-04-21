#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QSound>  //多媒体模块下的 音效头文件

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    // 配置场景

    // 设置固定大小
    setFixedSize(350, 588);

    // 设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币主场景");

    //退出按钮的实现
    connect(ui->actionExit, &QAction::triggered, [=](){
        this->close();
    });

    //开始界面的音效
    QSound * startSoud = new QSound(":/res/TapButtonSound.wav",this);
//    startSoud->setLoops(10); //-1 为无限循环
//    startSoud->play();


    // 开始按钮
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this); //放置到当前窗口
    startBtn->move( this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    // 实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听选择关卡的返回按钮的信号
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this, [=](){
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();
        this->show(); // 重新显示主场景
    });

    connect(startBtn, &MyPushButton::clicked, [=](){
//        qDebug() << "点击开始";

        //播放开始音效资源
        startSoud->play();

        // 使用弹起特效
        startBtn->bounce1();
        startBtn->bounce2();

        //延时进入到选择关卡的场景中
        QTimer::singleShot(500, this, [=](){
            // 设置chooseScene场景的位置
            chooseScene->setGeometry(this->geometry());

            //自身隐藏
            this->hide();
            //显示选择关卡场景
            chooseScene->show();

        });


    });

}

MainScene::~MainScene()
{
    delete ui;
}

//画背景图
void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //画背景图标
    pix.load(":/res/Title.png");

    pix = pix.scaled( pix.width() * 0.5, pix.height() * 0.5);

    painter.drawPixmap(10, 30, pix);

}

