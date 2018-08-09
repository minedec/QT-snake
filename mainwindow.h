#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameWidget.h"
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QIcon>
#include <QPalette>
#include <qbrush>
#include <QPixmap>
#include <QPushButton>
#include <QMessageBox>
#include <Qlabel>
#include <QFont>

class mainWidget:public QWidget //继承Qwidget类
{
     Q_OBJECT   //信号槽机制加上这个
public:
    mainWidget(QWidget *parent = 0);     //表示此控件不是某个控件的子控件
    ~mainWidget();   //析构函数，退出时调用
private:
    QPushButton *startbtn;  //开始按钮，鼠标点击
    QPushButton *endbtn;    //结束按钮，点击退出
    GameWidget *gamewidget;     //游戏界面控件
    QLabel *label;  //标题？
    QLabel *imglabel;
signals:
public slots:    //公共槽函数
    void endSlot();     //接受退出信号
    void startSlot();   //接受开始信号
};

#endif // MAINWINDOW_H
