#include "finishline.h"

finishLine::finishLine(int height, int width, QString sprite):basicObject(height,width,sprite)
{
}

finishLine::~finishLine()
{
    delete pixmap;
}
