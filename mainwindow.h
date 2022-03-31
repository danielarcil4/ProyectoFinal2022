#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QTimer>

#include "player.h"
#include "solidblock.h"
#include "bird.h"
#include "scorpion.h"
#include "marsh.h"

#define numRow 2
#define numCol numRow*2

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    void createMap();
    void createEnemies();

    int getScenePosX() const;
    void setScenePosX(int value);

    int getScenePosY() const;
    void setScenePosY(int value);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int scenePosX=-500,scenePosY=10;
    player *player1;
    QList<scorpion*> scorpionEnemies;
    QList<bird*> birdEnemies;
    QList<marsh*> marshEnemies;
    QList<solidBlock*> solidBlocks;
    QTimer *moving = new QTimer;
public slots:
    void move();
};
#endif // MAINWINDOW_H
