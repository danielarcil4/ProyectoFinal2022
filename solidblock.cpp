#include "solidblock.h"
#include <QDebug>


solidBlock::solidBlock(int height, int width, QString sprite):basicObject(height,width,sprite)
{
    connect(timer,&QTimer::timeout,this,&solidBlock::updateFloor);
    timer->start(50);
}

solidBlock::~solidBlock(){
    delete timer;
    delete pixmap;
}

void solidBlock::collidingInMove(int key)
{
    switch (key) {
        case Qt::Key_D:
            getPtrPlayers()[0]->setX(getPtrPlayers()[0]->x()-getPtrPlayers()[0]->getVx());
            break;
        case Qt::Key_A:
            getPtrPlayers()[0]->setX(getPtrPlayers()[0]->x()-getPtrPlayers()[0]->getVx());
            break;
        case Qt::Key_L:
            getPtrPlayers()[1]->setX(getPtrPlayers()[1]->x()-getPtrPlayers()[1]->getVx());
            break;
        case Qt::Key_J:
            getPtrPlayers()[1]->setX(getPtrPlayers()[1]->x()-getPtrPlayers()[1]->getVx());
            break;
    }

}

void solidBlock::updateFloor()
{
    for(short int i=0;i<getPtrPlayers().length();i++)
        if(abs(x()-getPtrPlayers()[i]->x())<40 and abs(y()-getPtrPlayers()[i]->y())>=80){
            getPtrPlayers()[i]->setFloor(y()-80);
            if(y()>=665)
                getPtrPlayers()[i]->setCollition(x());
        }
}

QList<player *> solidBlock::getPtrPlayers() const
{
    return ptrPlayers;
}

void solidBlock::setPtrPlayers(const QList<player *> &value)
{
    ptrPlayers = value;
}
