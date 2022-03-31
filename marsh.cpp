#include "marsh.h"
#include <QDebug>

marsh::marsh(int height,int width,QString sprite):basicObject(height,width,sprite)
{
    connect(timer,&QTimer::timeout,this,&marsh::slowDown);
    connect(returning,&QTimer::timeout,this,&marsh::returnSpeed);
    timer->start(500);
}

marsh::~marsh()
{
    delete returning;
    delete timer;
    delete pixmap;
}

void marsh::slowDown()
{
    if(getPtrPlayer()->x()>=x() and getPtrPlayer()->x()<=x()+200 and abs(y()-getPtrPlayer()->y())<=70){
        getPtrPlayer()->setVx(5);
        returning->start(2000);
    }
}

void marsh::returnSpeed()
{
    getPtrPlayer()->setVx(10);
    returning->stop();
}

player *marsh::getPtrPlayer() const
{
    return ptrPlayer;
}

void marsh::setPtrPlayer(player *value)
{
    ptrPlayer = value;
}

