#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include <QTimer>

#include "basicobject.h"

class player:public basicObject
{
private:
    int Vy=0,Vx=10,floor=625;
    int collition=0,numberPlayer=0;
    QTimer *fall = new QTimer;
    QTimer *recover = new QTimer;
public:
    player(int height,int width,QString sprite,int numberPlayer);
    ~player();

    void walk(int key);
    void getDamage();

    int getVy() const;
    void setVy(int value);

    int getVx() const;
    void setVx(int value);

    int getFloor() const;
    void setFloor(int value);

    int getCollition() const;
    void setCollition(int value);

    int getNumberPlayer() const;
    void setNumberPlayer(int value);

public slots:
    void gravity();
    void recoverVel();
};

#endif // PLAYER_H
