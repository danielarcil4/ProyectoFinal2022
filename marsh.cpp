#include "marsh.h"

QList<player *> marsh::getPtrPlayers() const
{
    return ptrPlayers;
}

void marsh::setPtrPlayers(const QList<player *> &value)
{
    ptrPlayers = value;
}

marsh::marsh(int height,int width,QString sprite):basicObject(height,width,sprite)
{
    connect(timer,&QTimer::timeout,this,&marsh::slowDown);
    timer->start(500);
}

marsh::~marsh()
{
    delete timer;
    delete pixmap;
}

void marsh::slowDown()
{
    for(short int i=0;i<getPtrPlayers().length();i++)
        if(getPtrPlayers()[i]->x()>=x() and getPtrPlayers()[i]->x()<=x()+200 and abs(y()-getPtrPlayers()[i]->y())<=70)
            getPtrPlayers()[i]->getDamage();

}


