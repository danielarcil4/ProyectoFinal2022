#ifndef SOLIDBLOCK_H
#define SOLIDBLOCK_H

#include <QTimer>
#include "basicobject.h"
#include "player.h"

class solidBlock: public basicObject
{
private:
    QList<player*> ptrPlayers;
    QTimer *timer = new QTimer;
public:
    solidBlock(int height,int width,QString sprite);
    ~solidBlock();

    void collidingInMove(int key);

    QList<player *> getPtrPlayers() const;
    void setPtrPlayers(const QList<player *> &value);

public slots:
    void updateFloor();
};

#endif // SOLIDBLOCK_H
