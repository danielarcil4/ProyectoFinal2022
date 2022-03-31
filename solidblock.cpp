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
            getPtrPlayer()->setX(getPtrPlayer()->x()-getPtrPlayer()->getVx());
            break;
        case Qt::Key_A:
            getPtrPlayer()->setX(getPtrPlayer()->x()-getPtrPlayer()->getVx());
            break;
    }
}

void solidBlock::updateFloor()
{
    /*if(abs(x()-getPtrPlayer()->x())<40 and abs(y()-getPtrPlayer()->y())<=40)
        getPtrPlayer()->setVx(0);*/

    if(abs(x()-getPtrPlayer()->x())<40 and abs(y()-getPtrPlayer()->y())>=80){
        getPtrPlayer()->setFloor(y()-80);
        if(y()>=665)
            getPtrPlayer()->setCollition(x());
    }
}

player *solidBlock::getPtrPlayer() const
{
    return ptrPlayer;
}

void solidBlock::setPtrPlayer(player *value)
{
    ptrPlayer = value;
}
