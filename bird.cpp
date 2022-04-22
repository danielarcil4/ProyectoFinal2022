#include "bird.h"


bird::bird(int height, int width, QString sprite,int x, int y):basicObject(height, width, sprite)
{
    setPivotPointX(x);
    setPivotPointY(y);
    hit = new QMediaPlayer;
    hit->setMedia(QUrl("qrc:/sprites/hit.mp3"));
    connect(move,&QTimer::timeout,this,&bird::Fly);
    move->start(100);
}

bird::~bird()
{
    delete move;
    delete pixmap;
}

void bird::beatUpPlayer()
{
    for(short int i=0;i<getPtrPlayers().length();i++)
        if(abs(x()-getPtrPlayers()[i]->x())<50 and abs(y()-getPtrPlayers()[i]->y())<50){
            getPtrPlayers()[i]->getDamage();
            hit->play();
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

QList<player *> bird::getPtrPlayers() const
{
    return ptrPlayers;
}

void bird::setPtrPlayers(const QList<player *> &value)
{
    ptrPlayers = value;
}
QTimer *bird::getMove() const
{
    return move;
}
