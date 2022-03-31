#include "bird.h"
#include<QDebug>


bird::bird(int height, int width, QString sprite,int x, int y):basicObject(height, width, sprite)
{
    setPivotPointX(x);
    setPivotPointY(y);
    connect(move,&QTimer::timeout,this,&bird::Fly);
    connect(beatUp,&QTimer::timeout,this,&bird::doDamage);
    move->start(100);
}

bird::~bird()
{
    delete beatUp;
    delete move;
    delete pixmap;
}

void bird::beatUpPlayer()
{
    if(abs(x()-getPtrPlayer()->x())<50 and abs(y()-getPtrPlayer()->y())<50){
        beatUp->start(1500);
        //lifeLost->play();
    }
}

void bird::Fly()
{
    beatUpPlayer();
    if(getAngle()>=MAX_ANGLE)
        setChangeAngle(getChangeAngle()*-1);
    if(getAngle()<=-MAX_ANGLE)
        setChangeAngle(5);
    if(getChangeAngle()==5){
        if(getCol()>=490 or getCol()<280)
            setCol(280);
        updateSprite(getCol()+70,getRow());
    }
    else{
        if(getCol()>=210)
            setCol(-70);
        updateSprite(getCol()+70,getRow());
    }

    setAngle(getAngle()+getChangeAngle());
    setX(getPivotPointX()+getLenght()*sin(getAngle()*3.1416/180));
    setY(getPivotPointY()+getLenght()*cos(getAngle()*3.1416/180));
}

void bird::doDamage()
{
    qDebug()<<"lost life";
    beatUp->stop();
}

int bird::getAngle() const
{
    return angle;
}

void bird::setAngle(int value)
{
    angle = value;
}

int bird::getLenght() const
{
    return lenght;
}

void bird::setLenght(int value)
{
    lenght = value;
}

int bird::getChangeAngle() const
{
    return changeAngle;
}

void bird::setChangeAngle(int value)
{
    changeAngle = value;
}

void bird::setPivotPointX(int value)
{
    pivotPointX = value;
}

void bird::setPivotPointY(int value)
{
    pivotPointY = value;
}

int bird::getPivotPointX() const
{
    return pivotPointX;
}

int bird::getPivotPointY() const
{
    return pivotPointY;
}
player *bird::getPtrPlayer() const
{
    return ptrPlayer;
}

void bird::setPtrPlayer(player *value)
{
    ptrPlayer = value;
}
