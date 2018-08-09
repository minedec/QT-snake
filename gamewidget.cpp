#include "GameWidget.h"
#include "mainwindow.h"
#define ROW 13
#define COL 16
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3  //顺时针

GameWidget::GameWidget(QWidget *parent):QWidget(parent)
{
    //重写构造函数
    //this->autoFillBackground(this);
    this->resize(500,260);  //设置窗口大小
    this->setMaximumSize(500,260);  //设置最大尺寸？
    this->setWindowIcon(QIcon("")); //设置窗口图标，使用qicon资源
    this->setWindowTitle("游戏开始");
    QPalette palette;
    palette.setBrush(QPalette::Window, Qt::white); //设置背景图片
    this->setPalette(palette);

    startbtn=new QPushButton("开始",this);
    startbtn->setGeometry(QRect(350,190,40,30));

    returnbtn=new QPushButton("返回",this);
    returnbtn->setGeometry(QRect(410,190,40,30));

    //设置使用字体
    QFont font;
    font.setFamily("Consolas");
    font.setBold(true);
    font.setPixelSize(25);
    //初始化分数等级
    score = 0;
    level = 0;
    //设置分数等级显示
    scorelabel = new QLabel("分数",this);
    scorelabel->setFont(font);
    scorelabel->setGeometry(QRect(360,20,60,30));

    levellabel = new QLabel("等级",this);
    levellabel->setFont(font);
    levellabel->setGeometry(QRect(360,50,60,30));

    //分数转化为字符串
    str1 = QString::number(score);
    str2 = QString::number(level);

    scoreshow = new QLabel(this);
    scoreshow->setFont(font);
    scoreshow->setGeometry(QRect(440,20,60,30));
    scoreshow->setText(str1);

    levelshow = new QLabel(this);
    levelshow->setFont(font);
    levelshow->setGeometry(QRect(440,50,60,30));
    levelshow->setText(str2);

    //按键绑定
    connect(this,SIGNAL(LeftSign()),this,SLOT(leftbtnSlot()));
    connect(this,SIGNAL(RightSign()),this,SLOT(rightbtnSlot()));
    connect(this,SIGNAL(UpSign()),this,SLOT(upbtnSlot()));
    connect(this,SIGNAL(DownSign()),this,SLOT(downbtnSlot()));
    connect(startbtn,SIGNAL(clicked()),this,SLOT(startbtnSlot()));
    connect(returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));

    //设置随机数种子
    QTime t;
    t=QTime::currentTime();
    qsrand(t.msec());
    //设置蛇头随机数
    snake[0][0] = qrand()%COL;
    snake[0][1] = qrand()%ROW;
   //设置食物随机位置
    food[0] = qrand()%COL;
    food[1] = qrand()%ROW;
    bool cover = true;
    while(cover)  //防止重叠
    {
        if(snake[0][0]==food[0] &&snake[0][1]==food[1])
        {
            food[0] = qrand()%COL;
            food[1] = qrand()%ROW;
            cover = true;
        }
        else
        {
            cover = false;
        }
     }
    //初始化计时器
    timer = new QTimer(this);
    interval = 500;
    timer->setInterval(interval);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timeoutSlot()));  //计时器绑定刷新函数
}

GameWidget::~GameWidget()
{
    delete startbtn;
    delete returnbtn;
    delete leftbtn;
    delete rightbtn;
    delete upbtn;
    delete downbtn;
    delete timer;
}

void GameWidget::upbtnSlot()
{
    if(direction ==DOWN)
    {
        return;  //防止自己吃到自己
    }
    else
    {
        direction = UP;
    }
}

void GameWidget::rightbtnSlot()
{
    if(direction == LEFT)
    {
        return;
    }
    else
    {
        direction = RIGHT;
    }
}

void GameWidget::downbtnSlot()
{
    if(direction == UP)
    {
        return;
    }
    else
    {
        direction = DOWN;
    }
}

void GameWidget::leftbtnSlot()
{
    if(direction ==RIGHT)
    {
        return;
    }
    else
    {
        direction = LEFT;
    }
}

void GameWidget::startbtnSlot()
{
    timer->start();
    interval = 500;
}

void GameWidget::returnbtnSlot()
{
    delete this;
}

//刷新函数,更新后台数据
void GameWidget::timeoutSlot()
{
    //食物
    if(food[0]==snake[0][0] &&food[1]==snake[0][1])
    {
        foodcount++;
        score++;
        str1 = QString::number(score);
        scoreshow->setText(str1);

        switch(score)
        {
        case 5:interval = 300;timer->setInterval(interval);level++;break;
        case 10:interval = 180;timer->setInterval(interval);level++;break;
        case 20:interval = 100;timer->setInterval(interval);level++;break;
            case 30:interval = 60;timer->setInterval(interval);level++;break;
            case 40:interval = 20;timer->setInterval(interval);level++;break;
            case 50:interval = 10;timer->setInterval(interval);level++;break;
        }

        str2 = QString::number(level);
        levelshow->setText(str2);

        QTime t;
        t = QTime::currentTime();
        qsrand(t.msec());

        food[0] = qrand() % COL;
        food[1] = qrand()%ROW;

        int i = 0;  //蛇身长度
        while(i<=foodcount)
        {
            if(snake[i][0]==food[0]&&snake[i][1]==food[1])
            {
                food[0]=qrand()%COL;
                food[1]=qrand()%ROW;
                i=0;
            }
            else
            {
                i++;
            }
        }
      }

        //增加尾巴长度
        if(foodcount==1)
        {
            switch(direction)
            {
            case UP:
                snake[foodcount][0] = snake[foodcount-1][0];
                snake[foodcount][1] = snake[foodcount-1][1]+1;
            case RIGHT:
                snake[foodcount][0] = snake[foodcount-1][0]-1;
                snake[foodcount][1] = snake[foodcount-1][1];
            case DOWN:
                snake[foodcount][0] = snake[foodcount-1][0];
                snake[foodcount][1] = snake[foodcount-1][1]-1;
            case LEFT:
                snake[foodcount][0] = snake[foodcount-1][0]+1;
                snake[foodcount][1] = snake[foodcount-1][1];
            }
        }
        else if(foodcount>=2)
        {
            if(snake[foodcount-2][0]==snake[foodcount-1][0]&&(snake[foodcount-2][1]-snake[foodcount-1][1])==-1)
            {
                snake[foodcount][0] = snake[foodcount-1][0];
                snake[foodcount][1] = snake[foodcount-1][1]+1;
            }
            else if(snake[foodcount-2][1]==snake[foodcount-1][1]&&(snake[foodcount-2][0]-snake[foodcount-1][0])==1)
            {
                snake[foodcount][0] = snake[foodcount-1][0]-1;
                snake[foodcount][1] = snake[foodcount-1][1];
            }
            else if(snake[foodcount-2][0]==snake[foodcount-1][0]&&(snake[foodcount-2][1]-snake[foodcount-1][1])==1)
            {
                snake[foodcount][0] = snake[foodcount-1][0];
                snake[foodcount][1] = snake[foodcount-1][1]-1;
            }
            else
            {
                snake[foodcount][0] = snake[foodcount-1][0]+1;
                snake[foodcount][1] = snake[foodcount-1][1];
            }
        }

        //蛇身移动
        int i;
        for(i = foodcount; i >=1 ; i--)
        {
            snake[i][0] = snake[i-1][0];
            snake[i][1] = snake[i-1][1];
        }

        //蛇头移动
        switch(direction)
        {
        case UP:
            snake[0][1]--;break;
        case RIGHT:
            snake[0][0]++;break;
        case DOWN:
            snake[0][1]++;break;
        case LEFT:
            snake[0][0]--;break;
        }

        //碰撞判断
        for(i = 1; i <= foodcount; i++)
        {
            //蛇头碰撞上蛇身
            if(snake[0][0]==snake[i][0] && snake[0][1]==snake[i][1])
            {

                timer->stop();
                if(QMessageBox::question(this,"提示","游戏结束，是否重来",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
                {
                    //重置
                    score = 0;
                    level = 0;
                    foodcount = 0;
                    str1=QString::number(score);
                    str2=QString::number(level);
                    scoreshow->setText(str1);
                    levelshow->setText(str2);

                    QTime t;
                    t=QTime::currentTime();
                    qsrand(t.msec());
                    snake[0][0] = qrand()%COL;
                    snake[0][1] = qrand()%ROW;
                    direction = qrand()%4;
                    food[0] = qrand()%COL;
                    food[1] = qrand()%ROW;
                    bool cover = true;
                    interval = 500;
                    while(cover)  //防止重叠
                    {
                        if(snake[0][0]==food[0] &&snake[0][1]==food[1])
                        {
                            food[0] = qrand()%COL;
                            food[1] = qrand()%ROW;
                            cover = true;
                        }
                        else
                        {
                            cover = false;
                        }
                     }
                    //timer->start();

                }
                return;

            }
        }

        //碰撞墙壁，从另一侧出来
        for(i = 0; i < COL; i++)
        {
            if(snake[0][0] == i &&snake[0][1]==-1 &&direction==UP)  //最上面的墙
            {
                snake[0][0]=i;
                snake[0][1]=ROW-1;
            }
            else if(snake[0][0] == i &&snake[0][1]== ROW &&direction==DOWN) //最下面的墙
            {
                snake[0][0]=i;
                snake[0][1]=0;
            }
        }
        for(i = 0; i < ROW; i++)
        {
            if(snake[0][0] == -1 &&snake[0][1]==i &&direction==LEFT)  //最上面的墙
            {
                snake[0][0]=COL-1;
                snake[0][1]=i;
            }
            else if(snake[0][0] == COL &&snake[0][1]==i&&direction==RIGHT) //最下面的墙
            {
                snake[0][0]=0;
                snake[0][1]=i;
            }
        }
        this->update();  //update（）会调用paintevent（）事件
}

//绘图事件
void GameWidget::paintEvent(QPaintEvent *)
{
    //绘制地图
    QPainter paint(this);
    for(int i = 0; i<ROW*20;i+=20)
    {
        for(int j = 0; j<COL*20;j+=20)
        {
            paint.drawRect(j,i,20,20);  //绘制方格
        }
    }
    //绘制食物
    paint.drawImage(food[0]*20,food[1]*20,QImage(":/images/red").scaled(QSize(20,20)));
    //绘制蛇
    for(int i = 0; i<=foodcount; i++)
    {
        paint.drawImage(snake[i][0]*20,snake[i][1]*20,QImage(":/images/green").scaled(QSize(20,20)));

    }
}

void GameWidget::keyPressEvent(QKeyEvent *key)
{

    //按键触发信号
    switch(key->key())
    {
    case Qt::Key_W:
        emit UpSign();
        break;
    case Qt::Key_D:
        emit RightSign();
        break;
    case Qt::Key_S:
        emit DownSign();
        break;
    case Qt::Key_A:
        emit LeftSign();
        break;
    }
}
