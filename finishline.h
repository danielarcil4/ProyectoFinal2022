#ifndef FINISHLINE_H
#define FINISHLINE_H

#include "basicobject.h"

class finishLine:public basicObject
{
public:
    finishLine(int height,int width,QString sprite);
    ~finishLine();
};

#endif // FINISHLINE_H
