#ifndef SCORPION_H
#define SCORPION_H

#include <QTimer>
#include <math.h>
#include <QPainter>
#include <QMediaPlayer>

#include "basicobject.h"
#include "player.h"

#define ANGLE 40

class scorpion:public basicObject
{
private:
    QTimer *fire = new QTimer;
    QTimer *moving = new QTimer;
    float t=0.0;
    int Vx=8,Vy=25;
    QMediaPlayer *hit;
    QList<player *> ptrPlayers;
    QGraphicsEllipseItem *bullet = new QGraphicsEllipseItem(x(),y(),10,10);

public:
    scorpion(int height,int width,QString sprite);
   ~scorpion();

    QGraphicsEllipseItem *getBullet() const;
    void setBullet(QGraphicsEllipseItem *value);

    float getT() const;
    void setT(float value);

    int getVx() const;
    void setVx(int value);

    int getVy() const;
    void setVy(int value);

    QList<player *> getPtrPlayers() const;
    void setPtrPlayers(const QList<player *> &value);

    QTimer *getFire() const;

public slots:
    void shot();
    void move();
};

#endif // SCORPION_H
