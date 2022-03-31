#include "player.h"
#include <QDebug>


player::player(int height, int width, QString sprite,int numberPlayer):basicObject(height,width,sprite)
{
    setNumberPlayer(numberPlayer);
    connect(recover,&QTimer::timeout,this,&player::recoverVel);
    connect(fall,&QTimer::timeout,this,&player::gravity);
    fall->start(50);
}


player::~player()
{
    delete recover;
    delete fall;
    delete pixmap;
}

void player::walk(int key)
{
    if(getNumberPlayer()==1)
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
    else if(getNumberPlayer()==2)
        switch (key) {
        case Qt::Key_Up:
                if(y()==getFloor())
                    setVy(-80);
                break;
            case Qt::Key_Right:
                setVx(abs(getVx()));
                setX(x()+getVx());

                if(getCol()<250 or getCol()>=550)
                    setCol(250);
                updateSprite(getCol()+50,0);
                break;
            case Qt::Key_Left:
                setVx(-abs(getVx()));
                setX(x()+getVx());

                if(getCol()>=250)
                    setCol(-50);
                updateSprite(getCol()+50,0);
                break;
        }

}

void player::getDamage()
{
    setVx(2);
    recover->start(2000);
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

void player::recoverVel()
{
    setVx(10);
    recover->stop();
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

int player::getNumberPlayer() const
{
    return numberPlayer;
}

void player::setNumberPlayer(int value)
{
    numberPlayer = value;
}
