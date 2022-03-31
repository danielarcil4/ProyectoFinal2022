#ifndef BASICOBJECT_H
#define BASICOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QList>

class basicObject:public QObject,public QGraphicsPixmapItem
{
protected:
    int height=0,width=0,col=0,row=0;
    QString sprite="";
    QPixmap *pixmap;

public:
    basicObject(int height,int width,QString sprite);
    void setSprite(const QString &value);
    void updateSprite(int col,int row);

    int getHeight() const;
    void setHeight(int value);
    int getWidth() const;
    void setWidth(int value);
    int getCol() const;
    void setCol(int value);
    int getRow() const;
    void setRow(int value);

    QPixmap *getPixmap() const;
};

#endif // BASICOBJECT_H
