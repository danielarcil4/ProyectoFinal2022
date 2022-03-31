#ifndef MARSH_H
#define MARSH_H

#include "basicobject.h"
#include "player.h"

class marsh:public basicObject
{
private:
    QList <player*> ptrPlayers;
    QTimer *timer = new QTimer;
public:
    marsh(int height,int width,QString sprite);
    ~marsh();

    QList<player *> getPtrPlayers() const;
    void setPtrPlayers(const QList<player *> &value);
public slots:
    void slowDown();
};

#endif // MARSH_H
