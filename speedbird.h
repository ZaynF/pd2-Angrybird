#ifndef SPEEDBIRD_H
#define SPEEDBIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class Speedbird : public GameItem
{
public:
    Speedbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouse);
};

#endif // SPEEDBIRD_H
