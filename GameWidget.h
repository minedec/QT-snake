#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPalette>
#include <QIcon>
#include <QPushButton>
#include <Qpainter>
#include <QDebug>
#include <QTime>
#include <Qtimer>
#include <QMessageBox>
#include <QKeyEvent>  //键盘事件
#include <QLabel>
#include <QFont>


class GameWidget:public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);  //explicit指定构造函数不作为隐式转换
    ~GameWidget();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *); //这两个好像是自带函数，对它们重写

private:
    //按钮相当于鼠标事件
    QPushButton *upbtn;
    QPushButton *leftbtn;
    QPushButton *downbtn;
    QPushButton *rightbtn;
    QPushButton *startbtn;
    QPushButton *returnbtn;

    int direction;  //记录蛇前进方向
    int snake[100][2];  //记录蛇的坐标
    int foodcount;  //记录所吃食物
    QTimer *timer;  //计时器！

    int food[2]; //记录食物坐标
    int score;
    int level;  //记录等级，后期加速用
    int interval;  //记录刷新时间间隔，增加难度

    QLabel *scorelabel;  //这个是显示标题
    QLabel *levellabel;
    QLabel *scoreshow;  //这个是显示变量
    QLabel *levelshow;
    QString str1,str2;


signals:
    //键盘事件与鼠标点击事件绑定，再和移动绑定
    void UpSign();
    void DownSign();
    void LeftSign();
    void RightSign();

public slots:
    //槽函数，绑定移动
    void upbtnSlot();
    void downbtnSlot();
    void leftbtnSlot();
    void rightbtnSlot();
    void startbtnSlot();
    void returnbtnSlot();

    void timeoutSlot();  //时间触发器？刷新器？
};

#endif // GAMEWIDGET_H
