#ifndef BIRD_H
#define BIRD_H

#include <math.h>
#include <QTimer>
#include "basicobject.h"
#include "player.h"
#define MAX_ANGLE 65

class bird:public basicObject
{
private:
    int angle = 0,lenght=300,changeAngle=5,pivotPointX=0,pivotPointY=0;
    player *ptrPlayer;
    QTimer *move = new QTimer;
    QTimer *beatUp = new QTimer;
public:
    bird(int height,int width,QString sprite,int x,int y);
    ~bird();

    void beatUpPlayer();

    int getAngle() const;
    void setAngle(int value);

    int getLenght() const;
    void setLenght(int value);

    int getChangeAngle() const;
    void setChangeAngle(int value);

    int getPivotPointX() const;

    void setPivotPointX(int value);

    int getPivotPointY() const;

    void setPivotPointY(int value);

    player *getPtrPlayer() const;
    void setPtrPlayer(player *value);

private slots:
    void Fly();
    void doDamage();
};

#endif // BIRD_H
