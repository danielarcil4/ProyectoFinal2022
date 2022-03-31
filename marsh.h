#ifndef MARSH_H
#define MARSH_H

#include "basicobject.h"
#include "player.h"

class marsh:public basicObject
{
private:
    player *ptrPlayer;
    QTimer *timer = new QTimer;
    QTimer *returning = new QTimer;
public:
    marsh(int height,int width,QString sprite);
    ~marsh();

    player *getPtrPlayer() const;
    void setPtrPlayer(player *value);
public slots:
    void returnSpeed();
    void slowDown();
};

#endif // MARSH_H
