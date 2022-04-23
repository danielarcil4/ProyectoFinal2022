#ifndef POINT_H
#define POINT_H

#include "basicobject.h"
#include "player.h"

class point:public basicObject
{
public:
    point(int height, int width, QString sprite);

};

#endif // POINT_H
