#include "scorpion.h"
#include <QDebug>

QTimer *scorpion::getFire() const
{
    return fire;
}

scorpion::scorpion(int height, int width, QString sprite):basicObject(height,width,sprite)
{
    connect(fire,&QTimer::timeout,this,&scorpion::shot);
    connect(moving,&QTimer::timeout,this,&scorpion::move);
    fire->start(50);
    moving->start(250);
    getBullet()->setPos(x(),y()-50);
    hit = new QMediaPlayer;
    hit->setMedia(QUrl("qrc:/sprites/hit.mp3"));
}

scorpion::~scorpion()
{
    delete bullet;
    delete fire;
    delete pixmap;
}

void scorpion::shot()
{
    for(short int i=0;i<getPtrPlayers().length();i++)
        if(abs(getBullet()->x()-getPtrPlayers()[i]->x())<10 and abs(getBullet()->y()-getPtrPlayers()[i]->y())<30){
            getPtrPlayers()[i]->getDamage();
            hit->play();
        }

    setT(getT()+0.2);
    getBullet()->setPos(getBullet()->x()+Vx*cos(ANGLE*3.1416/180)*getT(),getBullet()->y()-Vy*sin(ANGLE*3.1416/180)*getT()+4.9*pow(getT(),2));
    getBullet()->setBrush(Qt::lightGray);
    if(getBullet()->y()>700){
        getBullet()->setPos(x()+20,y()+40);
        setT(0);
    }
}

void scorpion::move()
{
    if(getCol()>=150)
        setCol(-50);
    updateSprite(getCol()+50,0);
}

QGraphicsEllipseItem *scorpion::getBullet() const
{
    return bullet;
}

void scorpion::setBullet(QGraphicsEllipseItem *value)
{
    bullet = value;
}

float scorpion::getT() const
{
    return t;
}

void scorpion::setT(float value)
{
    t = value;
}

int scorpion::getVx() const
{
    return Vx;
}

void scorpion::setVx(int value)
{
    Vx = value;
}

int scorpion::getVy() const
{
    return Vy;
}

void scorpion::setVy(int value)
{
    Vy = value;
}
QList<player *> scorpion::getPtrPlayers() const
{
    return ptrPlayers;
}

void scorpion::setPtrPlayers(const QList<player *> &value)
{
    ptrPlayers = value;
}
