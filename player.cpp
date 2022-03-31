#include "player.h"
#include <QDebug>


player::player(int height, int width, QString sprite):basicObject(height,width,sprite)
{
    connect(fall,&QTimer::timeout,this,&player::gravity);
    fall->start(50);
}

player::~player()
{
    delete fall;
    delete pixmap;
}

void player::walk(int key)
{
    switch (key) {
        case Qt::Key_W:
            if(y()==getFloor())
                setVy(-80);
            break;
        case Qt::Key_D:
            setVx(abs(getVx()));
            setX(x()+getVx());

            if(getCol()<250 or getCol()>=550)
                setCol(250);
            updateSprite(getCol()+50,0);
            break;
        case Qt::Key_A:
            setVx(-abs(getVx()));
            setX(x()+getVx());

            if(getCol()>=250)
                setCol(-50);
            updateSprite(getCol()+50,0);
            break;
    }

}

void player::gravity()
{
    if(abs(x()-getCollition())>40)
        setFloor(625);
    setY(y()+getVy());
    if(y()<getFloor()){
        setVy(20);
        setX(x()+getVx()*2);
    }
    else
        setVy(0);
}

int player::getVy() const
{
    return Vy;
}

void player::setVy(int value)
{
    Vy = value;
}

int player::getVx() const
{
    return Vx;
}

void player::setVx(int value)
{
    Vx = value;
}

int player::getFloor() const
{
    return floor;
}

void player::setFloor(int value)
{
    floor = value;
}

int player::getCollition() const
{
    return collition;
}

void player::setCollition(int value)
{
    collition = value;
}
