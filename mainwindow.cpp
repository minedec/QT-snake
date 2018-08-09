#include "mainwindow.h"

mainWidget::mainWidget(QWidget *parent):QWidget(parent)
{
    //重写构造函数
    this->resize(500,500);  //设置窗口大小
    this->setMaximumSize(500,500);  //设置最大尺寸？
    this->setWindowIcon(QIcon("")); //设置窗口图标，使用qicon资源
    this->setWindowTitle("贪吃蛇");
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/images/bg").scaled(this->size()))); //设置背景图片
    palette.setColor(QPalette::WindowText,Qt::white);
    this->setPalette(palette);

    startbtn = new QPushButton(this);
    startbtn ->setIcon(QIcon(":/images/love"));  //设置开始按钮图标
    startbtn->setIconSize(QSize(200,200));  //设置图标大小
    startbtn->setGeometry(QRect(330,70,100,100));  //设置图标位置？
    startbtn->setFlat(true);

    endbtn = new QPushButton(this);
    endbtn ->setIcon(QIcon(":/images/gameexit"));
    endbtn->setIconSize(QSize(200,200));
    endbtn->setGeometry(QRect(330,160,100,100));
    endbtn->setFlat(true);

    //设置标题栏
    QFont font;
    font.setFamily("Consolas");
    font.setBold(true);
    font.setPixelSize(30);

    label = new QLabel(this);
    label->setText("贪吃蛇\nWASD移动");
    label->setFont(font);
    label->setGeometry(QRect(100,10,300,100));  //setgeometry函数设置在父窗口相对位置大小

    imglabel = new QLabel(this);
    imglabel->setPixmap(QPixmap(":/images/snake").scaled(250,250));
    imglabel->setGeometry(QRect(30,140,250,250));

    QObject::connect(endbtn,SIGNAL(clicked()),this,SLOT(endSlot()));
    QObject::connect(startbtn,SIGNAL(clicked()),this,SLOT(startSlot()));
}

mainWidget::~mainWidget()  //重写析构函数
{
    delete startbtn;
    delete endbtn;
}

void mainWidget::endSlot()
{
    if(QMessageBox::question(this,"退出","确定退出?",QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
    {
        delete this;
        exit(0);
    }
}

void mainWidget::startSlot()
{
    gamewidget = new GameWidget;
    gamewidget->show();
}

