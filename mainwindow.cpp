#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(QImage(":/sprites/MapGame.jpeg")));
    //scene->setSceneRect(getScenePosX(),getScenePosY(),ui->graphicsView->width(),ui->graphicsView->height());

    player1 = new player(80,50,":/sprites/player1.png");
    player1->setPos(-400,625);

    createMap();
    createEnemies();

    scene->addItem(player1);
    connect(moving,SIGNAL(timeout()),this,SLOT(move()));
    moving->start(10);
}

MainWindow::~MainWindow()
{
    for(short int i=0;i<scorpionEnemies.length();i++)
        delete scorpionEnemies[i];
    for(short int i=0;i<birdEnemies.length();i++)
        delete birdEnemies[i];
    for(short int i=0;i<solidBlocks.length();i++)
        delete solidBlocks[i];
    delete player1;
    delete scene;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    player1->walk(event->key());
    for (short int i=0;i<solidBlocks.length();i++)
        if(abs(solidBlocks[i]->x()-player1->x())<40 and abs(solidBlocks[i]->y()-player1->y())<=40){
            solidBlocks[i]->collidingInMove(event->key());
        }
}

void MainWindow::createMap()
{
    for (short int numPiramides=0;numPiramides<3;numPiramides++)
        for(short int row=0,y=625-(40*numPiramides);row<numRow+numPiramides;row++,y+=40)
            for(short int col=0,x=0;col<numCol+(numRow+numPiramides)*2;x+=40,col++){
                if(col==0){
                    if(numPiramides==0)
                        x-=80;
                    for(short int i=0,inc=1;i<numPiramides;i++,inc-=2)
                        x+=80*numPiramides+inc+200;
                }

                if(col>=numRow+numPiramides-row and col<=numRow+numPiramides+row){
                    solidBlocks.push_back(new solidBlock(40,40,":/sprites/solidBlock.png"));
                    solidBlocks.back()->setPos(x,y);
                }
            }


    for(short int row=0,y=545;row<numRow+2;row++,y+=40)
        for(short int col=0,x=1700;col<numCol+4;x+=40,col++)
            if(col>=numRow+2-row and col<=numRow+2+row ){
                solidBlocks.push_back(new solidBlock(40,40,":/sprites/solidBlock.png"));
                solidBlocks.back()->setPos(x,y);
            }

    for (short int numPiramides=2;numPiramides>=0;numPiramides--)
        for(short int row=0,y=625-(40*numPiramides);row<numRow+numPiramides;row++,y+=40)
            for(short int col=0,x=3500;col<numCol+(numRow+numPiramides)*2;x+=40,col++){
                if(col==0){
                    if(numPiramides==0)
                        x+=80;
                    for(short int i=0,inc=1;i<numPiramides;i++,inc-=2)
                        x-=80*numPiramides+inc+300;
                }
                if(col>=numRow+numPiramides-row and col<=numRow+numPiramides+row){
                    solidBlocks.push_back(new solidBlock(40,40,":/sprites/solidBlock.png"));
                    solidBlocks.back()->setPos(x,y);
                }
            }

    for(short int i=0;i<solidBlocks.length();i++){
        solidBlocks[i]->setPtrPlayer(player1);
        scene->addItem(solidBlocks[i]);
    }

}

void MainWindow::createEnemies()
{
    for(short int i=0,x=1530;i<2;i++,x+=650){
        birdEnemies.push_back(new bird(70,70,":/sprites/EnemyBird.png",x,300));
        birdEnemies.back()->setPtrPlayer(player1);
        scene->addItem(birdEnemies.back());
    }

    for(short int i=0,x=-120;i<3;i++,x+=360){
        scorpionEnemies.push_back(new scorpion(50,50,":/sprites/scorpion.PNG"));
        scorpionEnemies.back()->setPos(x,655);
        scene->addItem(scorpionEnemies.back()->getBullet());
        scene->addItem(scorpionEnemies.back());    
    }
    //adjust Vy of third scorpion
    scorpionEnemies.back()->setVy(28);

    for(short int i=0,x=2925;i<2;i++,x+=450){
        marshEnemies.push_back(new marsh(20,200,":/sprites/marsh.png"));
        marshEnemies.back()->setPos(x,695);
        marshEnemies.back()->setPtrPlayer(player1);
        scene->addItem(marshEnemies.back());
    }
    for(short int i=0,x=3740;i<3;i++,x+=200){
        marshEnemies.push_back(new marsh(20,200,":/sprites/marsh.png"));
        marshEnemies.back()->setPos(x,695);
        marshEnemies.back()->setPtrPlayer(player1);
        scene->addItem(marshEnemies.back());
    }
}

void MainWindow::move()
{
    setScenePosX(getScenePosX()+2);
    scene->setSceneRect(getScenePosX(),getScenePosY(),ui->graphicsView->width()-5,ui->graphicsView->height()-5);
}

int MainWindow::getScenePosX() const
{
    return scenePosX;
}

void MainWindow::setScenePosX(int value)
{
    scenePosX = value;
}

int MainWindow::getScenePosY() const
{
    return scenePosY;
}

void MainWindow::setScenePosY(int value)
{
    scenePosY = value;
}
