#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    textEdit1 = new QPlainTextEdit(this);
    textEdit1->setVisible(false);

    textEdit2 = new QPlainTextEdit(this);
    textEdit2->setVisible(false);

    comboBox = new QComboBox(this);
    comboBox->setVisible(false);

    label_3 = new QLabel(this);
    label_3->setVisible(false);

    label_4 = new QLabel(this);
    label_4->setVisible(false);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::saveNewGame);
}

MainWindow::~MainWindow()
{
    for(short int i=0;i<scorpionEnemies.length();i++)
        delete scorpionEnemies[i];
    for(short int i=0;i<birdEnemies.length();i++)
        delete birdEnemies[i];
    for(short int i=0;i<solidBlocks.length();i++)
        delete solidBlocks[i];
    for(short int i=0;i<players.length();i++)
        delete players[i];
    delete view;
    delete scene;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    for(short int i=0;i<players.length();i++)
        players[i]->walk(event->key());
    for(short int I=0;I<players.length();I++)
        for (short int i=0;i<solidBlocks.length();i++)
            if(abs(solidBlocks[i]->x()-players[I]->x())<40 and abs(solidBlocks[i]->y()-players[I]->y())<=40){
                solidBlocks[i]->collidingInMove(event->key());
            }
}

void MainWindow::startGame()
{
    scene = new QGraphicsScene;

    scene->setBackgroundBrush(QBrush(QImage(":/sprites/MapGame.jpeg")));
    //scene->setSceneRect(getScenePosX(),getScenePosY(),ui->graphicsView->width(),ui->graphicsView->height());


    players.push_back(new player(80,50,":/sprites/player1.png",1));
    players.push_back(new player(80,50,":/sprites/player2.png",2));

    players[0]->setPos(-400,625);
    players[1]->setPos(-360,625);

    createMap();
    createEnemies();

    clock = new ownClock("TIME: ",0);
    scene->addItem(clock);
    clock->setPos(0,0);

    for(short int i=0;i<players.length();i++)
        scene->addItem(players[i]);
    connect(moving,SIGNAL(timeout()),this,SLOT(move()));
    moving->start(50);

    this->setGeometry(0,20,1930,1000);

    view = new QGraphicsView(scene,this);
    view->setGeometry(0,0,1920,1080);
    view->show();
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

    for(short int I=0;I<players.length();I++)
        for(short int i=0;i<solidBlocks.length();i++){
            solidBlocks[i]->setPtrPlayer(players[I]);
            scene->addItem(solidBlocks[i]);
        }

}

void MainWindow::createEnemies()
{
    //SET BIRD ENEMIES
    for(short int I=0;I<players.length();I++)
        for(short int i=0,x=1530;i<2;i++,x+=650){
            birdEnemies.push_back(new bird(70,70,":/sprites/EnemyBird.png",x,300));
            birdEnemies.back()->setPtrPlayer(players[I]);
            scene->addItem(birdEnemies.back());
        }
    //SET SCORPION ENEMIES
    for(short int i=0,x=-120;i<3;i++,x+=360){
        scorpionEnemies.push_back(new scorpion(50,50,":/sprites/scorpion.PNG"));
        scorpionEnemies.back()->setPos(x,655);
        scene->addItem(scorpionEnemies.back()->getBullet());
        scene->addItem(scorpionEnemies.back());    
    }
    //adjust Vy of third scorpion
    scorpionEnemies.back()->setVy(28);

    //SET MARSH ENEMIES
    for(short int I=0;I<players.length();I++)
        for(short int i=0,x=2925;i<2;i++,x+=450){
            marshEnemies.push_back(new marsh(20,200,":/sprites/marsh.png"));
            marshEnemies.back()->setPos(x,695);
            marshEnemies.back()->setPtrPlayer(players[I]);
            scene->addItem(marshEnemies.back());
        }
    for(short int I=0;I<players.length();I++)
        for(short int i=0,x=3740;i<3;i++,x+=200){
            marshEnemies.push_back(new marsh(20,200,":/sprites/marsh.png"));
            marshEnemies.back()->setPos(x,695);
            marshEnemies.back()->setPtrPlayer(players[I]);
            scene->addItem(marshEnemies.back());
        }
}


void MainWindow::move()
{
    setScenePosX(getScenePosX()+2);
    scene->setSceneRect(getScenePosX(),getScenePosY(),view->width()-5,view->height()-5);
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

//delete all but one botton and label
void MainWindow::setScenePosY(int value)
{
    scenePosY = value;
}

void MainWindow::deleteMenu()
{
    //ui->label_2->deleteLater();
    ui->verticalLayout->deleteLater();
    ui->pushButton->deleteLater();
    ui->pushButton_3->deleteLater();
    ui->pushButton_4->deleteLater();
}

void MainWindow::deleteNewGame()
{
    delete ui->pushButton_2;
    delete ui->label;
    delete ui->label_2;
    delete comboBox;
    delete label_4;
    delete textEdit2;
    delete label_3;
    delete textEdit1;
}

//new game
void MainWindow::on_pushButton_clicked()
{
    deleteMenu();
    ui->label_2->setText("NAME PLAYER 1:");
    ui->label_2->setStyleSheet("font: 28pt Onyx");

    textEdit1->setPlaceholderText("NAME");
    textEdit1->setVisible(true);
    textEdit1->setGeometry(220,110,300,30);

    label_3->setVisible(true);
    label_3->setText("NAME PLAYER 2:");
    label_3->setStyleSheet("font: 28pt Onyx");
    label_3->setGeometry(220,140,200,100);

    textEdit2->setPlaceholderText("NAME");
    textEdit2->setVisible(true);
    textEdit2->setGeometry(220,220,300,30);

    label_4->setVisible(true);
    label_4->setText("DIFFICULTY:");
    label_4->setStyleSheet("font: 28pt Onyx");
    label_4->setGeometry(220,300,200,100);

    comboBox->addItem("Easy");
    comboBox->addItem("Normal");
    comboBox->addItem("Hard");
    comboBox->setVisible(true);
    comboBox->setGeometry(220,380,300,30);

    ui->pushButton_2->setGeometry(50,250,300,50);
    ui->pushButton_2->setText("Start");

}

void MainWindow::saveNewGame()
{
    QFile file("../Proyectofinal2022/DB/games.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream write(&file);
    write<<textEdit1->toPlainText()<<'\n'<<"-400,625,0,3,100,"<<comboBox->currentText();

    deleteNewGame();
    startGame();
}

//load game
void MainWindow::on_pushButton_4_clicked()
{
    deleteMenu();

    QFile file("../Proyectofinal2022/DB/games.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream read(&file);
    QString line = read.readLine();
    QList<QString> loadGame;
    while (!line.isNull()) {
        comboBox->addItem(line);
        line = read.readLine();
        loadGame = line.split(',');
        players[0]->setPos(loadGame[0].toInt(nullptr,10),loadGame[1].toInt(nullptr,10));
        clock->setTimeClock(loadGame[2].toInt(nullptr,10));

        line = read.readLine();
    }

    comboBox->setVisible(true);
    comboBox->setGeometry(250,150,300,30);

    ui->pushButton_2->setGeometry(80,0,300,50);
    ui->pushButton_2->setText("Load");
}
