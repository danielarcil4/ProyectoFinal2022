#ifndef SOLIDBLOCK_H
#define SOLIDBLOCK_H

#include <QTimer>
#include "basicobject.h"
#include "player.h"

class solidBlock: public basicObject
{
private:
    player *ptrPlayer;
    QTimer *timer = new QTimer;
public:
    solidBlock(int height,int width,QString sprite);
    ~solidBlock();

    void collidingInMove(int key);

    player *getPtrPlayer() const;
    void setPtrPlayer(player *value);

public slots:
    void updateFloor();
};

#endif // SOLIDBLOCK_H
