#include "basicobject.h"


basicObject::basicObject(int height, int width, QString sprite)
{
    setHeight(height);
    setWidth(width);
    pixmap = new QPixmap(sprite);
    setPixmap(pixmap->copy(getCol(),getRow(),getWidth(),getHeight()));
}

void basicObject::setSprite(const QString &value)
{
    delete pixmap;
    pixmap = new QPixmap(value);
}

void basicObject::updateSprite(int col,int row)
{
    setCol(col);
    setRow(row);
    setPixmap(pixmap->copy(getCol(),getRow(),getWidth(),getHeight()));
}

int basicObject::getWidth() const
{
    return width;
}

void basicObject::setWidth(int value)
{
    width = value;
}

int basicObject::getCol() const
{
    return col;
}

void basicObject::setCol(int value)
{
    col = value;
}

int basicObject::getRow() const
{
    return row;
}

void basicObject::setRow(int value)
{
    row = value;
}

int basicObject::getHeight() const
{
    return height;
}

void basicObject::setHeight(int value)
{
    height = value;
}
QPixmap *basicObject::getPixmap() const
{
    return pixmap;
}
