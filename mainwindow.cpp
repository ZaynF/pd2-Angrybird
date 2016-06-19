#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
    repeat = 0;
    b=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);

    QImage bg;
    bg.load(":image/BACKGROUND.png");
    bg = bg.scaled(width(),ui->graphicsView->height());
    scene->setBackgroundBrush(bg);
    //scene->Init(0);

    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(width()/32*32,height()/18*3),world,scene));

    bar1 = new Barrier(16.0f,6.0f,2.0f,3.0f,&timer,QPixmap(":/image/barrier1.png").scaled(width()/32*2,height()/18*3),world,scene);
    itemList.push_back(bar1);

    bar2 = new Barrier(20.0f,6.0f,1.0f,5.0f,&timer,QPixmap(":/image/barrier2.png").scaled(width()/32*1,height()/18*5),world,scene);
    itemList.push_back(bar2);

    bar3 = new Barrier(24.0f,6.0f,1.0f,5.0f,&timer,QPixmap(":/image/barrier2.png").scaled(width()/32*1,height()/18*5),world,scene);
    itemList.push_back(bar3);

    bar4 = new Barrier(22.0f,8.0f,6.0f,1.0f,&timer,QPixmap(":/image/barrier3.png").scaled(width()/32*6,height()/18*1),world,scene);
    itemList.push_back(bar3);

    bar5 = new Barrier(26.0f,6.0f,1.0f,8.0f,&timer,QPixmap(":/image/barrier2.png").scaled(width()/32*1,height()/18*8),world,scene);
    itemList.push_back(bar5);

    bar6 = new Barrier(28.0f,6.0f,2.0f,3.0f,&timer,QPixmap(":/image/barrier1.png").scaled(width()/32*2,height()/18*3),world,scene);
    itemList.push_back(bar6);

    bar7 = new Barrier(28.0f,10.0f,2.0f,3.0f,&timer,QPixmap(":/image/barrier1.png").scaled(width()/32*2,height()/18*3),world,scene);
    itemList.push_back(bar7);

    bar8 = new Barrier(28.0f,14.0f,2.0f,3.0f,&timer,QPixmap(":/image/barrier1.png").scaled(width()/32*2,height()/18*3),world,scene);
    itemList.push_back(bar8);


    pig1 = new Pig(16.0f,8.0f,1.0f,&timer,QPixmap(":/image/pig1.png").scaled(height()/9.0,height()/9.0),world,scene);
    pig2 = new Pig(22.0f,5.0f,1.0f,&timer,QPixmap(":/image/pig1.png").scaled(height()/9.0,height()/9.0),world,scene);
    pig3 = new Pig(22.0f,10.0f,1.0f,&timer,QPixmap(":/image/pig1.png").scaled(height()/9.0,height()/9.0),world,scene);
    pig4 = new Pig(28.0f,18.0f,1.0f,&timer,QPixmap(":/image/pig1.png").scaled(height()/9.0,height()/9.0),world,scene);

    bgm = new QSound(":/image/The Beginning1.wav");
    bgm->play();

    // Create bird (You can edit here)

    rand_list.push_back(1);
    rand_list.push_back(2);
    rand_list.push_back(3);
    rand_list.push_back(4);

    for(int i=0;i<4;i++)
    {
        if(rand_list[i]==1)
        {
            birdie1 = new Bird(0.0f,4.0f,1.0f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
            // Setting the Velocity
            birdie1->setLinearVelocity(b2Vec2(0,0));
            birdlist.push_back(birdie1);
        }

        else if(rand_list[i]==2)
        {
            birdie2 = new Bird(0.0f,4.0f,1.0f,&timer,QPixmap(":/image/speed.png").scaled(height()/9.0,height()/9.0),world,scene);
            // Setting the Velocity
            birdie2->setLinearVelocity(b2Vec2(0,0));
            birdlist.push_back(birdie2);
        }
        else if(rand_list[i]==3)
        {
            birdie3 = new Bird(0.0f,4.0f,1.0f,&timer,QPixmap(":/image/bomb.png").scaled(height()/9.0,height()/9.0),world,scene);
            birdie3->setLinearVelocity(b2Vec2(0,0));
            birdlist.push_back(birdie3);
        }
        else if(rand_list[i]==4)
        {
            birdie4 = new Bird(0.0f,4.0f,1.0f,&timer,QPixmap(":/image/png+icon/green.png").scaled(height()/9.0,height()/9.0),world,scene);
            birdie4->setLinearVelocity(b2Vec2(0,0));
            birdlist.push_back(birdie4);
        }
    }

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
        if(event->type() == QEvent::MouseButtonPress)
        {
        /* TODO : add your code here */


            if(repeat==0)
            {
                std::cout << "Press !" << std::endl ;
                repeat=1;
            }

        }
        if(event->type() == QEvent::MouseMove)
        {
            /* TODO : add your code here */

            if(repeat==1)
            {
                QMouseEvent *me = dynamic_cast<QMouseEvent *>(event);
                pt.setX((me->pos().x()) * GameItem::g_worldsize.width()/GameItem::g_windowsize.width());
                pt.setY((1.0f-(me->pos().y())/GameItem::g_windowsize.height()) * GameItem::g_worldsize.height());
                birdlist[b]->g_body->SetActive(false);
                birdlist[b]->g_body->SetTransform(b2Vec2(pt.x(),pt.y()),0);
                std::cout << pt.x()<<" "<<pt.y() << std::endl ;
            }
        }
        if(event->type() == QEvent::MouseButtonRelease)
        {
            /* TODO : add your code here */
            std::cout << "Release !" << std::endl ;
            if(repeat==1)
            {
                int xn=sqrt((64-pt.x()*pt.x()));
                int yn=sqrt((81-pt.y()*pt.y()));
                birdlist[b]->g_body->SetActive(true);
                ;
                birdlist[b]->setLinearVelocity(b2Vec2(5*xn/2.5,5*yn/2.5));
                b=b+1;
                repeat = 0;
            }

        }
        return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    for(int i=0;i<4;i++)
    {
        if(event->key()==Qt::Key_2)
        {
            if(rand_list[i]==2)
            {
                birdlist[i]->setLinearVelocity(b2Vec2(20,-10));
                birdlist.push_back(birdie2);
            }
        }

        if(event->key()==Qt::Key_3)
        {
            if(rand_list[i]==3)
            {
                birdie5 = new Bird(birdlist[i]->g_body->GetPosition().x,birdlist[i]->g_body->GetPosition().y,1.0f,&timer,QPixmap(":/image/flame.png").scaled(height()/9.0,height()/9.0),world,scene);
                birdie5->setLinearVelocity(b2Vec2(10,-10));
                birdlist.push_back(birdie5);

            }
        }

        if(event->key()==Qt::Key_4)
        {
            if(rand_list[i]==4)
            {
                birdie6 = new Bird(birdlist[i]->g_body->GetPosition().x,birdlist[i]->g_body->GetPosition().y,1.0f,&timer,QPixmap(":/image/png+icon/green.png").scaled(height()/9.0,height()/9.0),world,scene);
                birdie6->setLinearVelocity(b2Vec2(10,-10));
                birdlist.push_back(birdie6);

                birdie7 = new Bird(birdlist[i]->g_body->GetPosition().x,birdlist[i]->g_body->GetPosition().y,1.0f,&timer,QPixmap(":/image/png+icon/green.png").scaled(height()/9.0,height()/9.0),world,scene);
                birdie7->setLinearVelocity(b2Vec2(10,-7.5));
                birdlist.push_back(birdie7);
            }
        }

        if(event->key()==Qt::Key_5)
        {
            birdie4->g_size.setHeight(4);
            birdie4->g_pixmap.setScale(height()/288.0);
            birdie4->setLinearVelocity(b2Vec2(10,-5));
            birdlist.push_back(birdie4);

            birdie6->g_size.setHeight(4);
            birdie6->g_pixmap.setScale(height()/288.0);
            birdie6->setLinearVelocity(b2Vec2(10,-10));
            birdlist.push_back(birdie6);

            birdie7->g_size.setHeight(4);
            birdie7->g_pixmap.setScale(height()/288.0);
            birdie7->setLinearVelocity(b2Vec2(10,-7.5));
            birdlist.push_back(birdie7);
        }

        if(event->key()==Qt::Key_Q)
        {
            if(rand_list[i]==1)
            {
                birdie1->g_pixmap.setPixmap(QPixmap(":/image/poro.png").scaled(height()/9.0,height()/9.0));
            }
        }

        if(event->key()==Qt::Key_W)
        {
            if(rand_list[i]==2)
            {
                birdie2->g_pixmap.setPixmap(QPixmap(":/image/malphite_poro.png").scaled(height()/9.0,height()/9.0));
            }
        }

        if(event->key()==Qt::Key_E)
        {
            if(rand_list[i]==3)
            {
                birdie3->g_pixmap.setPixmap(QPixmap(":/image/ahri_poro.png").scaled(height()/9.0,height()/9.0));
                birdie5->g_pixmap.setPixmap(QPixmap(":/image/love.png").scaled(height()/9.0,height()/9.0));
            }
        }

        if(event->key()==Qt::Key_R)
        {
            if(rand_list[i]==4)
            {
                birdie4->g_pixmap.setPixmap(QPixmap(":/image/renekton_poro.png").scaled(height()/9.0,height()/9.0));
                birdie6->g_pixmap.setPixmap(QPixmap(":/image/renekton_poro.png").scaled(height()/9.0,height()/9.0));
                birdie7->g_pixmap.setPixmap(QPixmap(":/image/renekton_poro.png").scaled(height()/9.0,height()/9.0));
            }
        }

        if(event->key()==Qt::Key_D)
        {

        }
    }
}
