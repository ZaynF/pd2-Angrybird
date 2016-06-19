#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QList>
#include <QKeyEvent>
#include <QSound>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <speedbird.h>
#include <barrier.h>
#include <pig.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *keye);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouse);
    Bird *birdie1;
    Bird *birdie2;
    Bird *birdie3;
    Bird *birdie4;
    Bird *birdie5;
    Bird *birdie6;
    Bird *birdie7;

    Barrier *bar1;
    Barrier *bar2;
    Barrier *bar3;
    Barrier *bar4;
    Barrier *bar5;
    Barrier *bar6;
    Barrier *bar7;
    Barrier *bar8;

    Pig *pig1;
    Pig *pig2;
    Pig *pig3;
    Pig *pig4;

    QPointF pt;
    QSound *bgm;
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<int> rand_list;
    QList<GameItem *> itemList;
    QList<Bird *>birdlist;
    QTimer timer;
    int repeat;
    static QSizeF g_worldsize, g_windowsize;
    int  b;
};

#endif // MAINWINDOW_H
