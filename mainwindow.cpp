#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Main menu
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

    load = new QPushButton(this);
    load->setVisible(false);

    saveInMenu = new QPushButton(this);
    saveInMenu->setVisible(false);

    //player
    players.push_back(new player(80,50,":/sprites/player1.png",1));
    players.push_back(new player(80,50,":/sprites/player2.png",2));

    clock = new ownClock("TIME: ",0);
    scoreP1 = new score("SCORE Player 1  ",0);
    scoreP2 = new score("SCORE Player 2  ",0);

    connect(saveInMenu, &QPushButton::clicked, this, &MainWindow::saveNewGame);
    connect(load, &QPushButton::clicked, this, &MainWindow::LoadGame);

}

MainWindow::~MainWindow()
{
    delete warning;
    delete eliminationP1;
    delete eliminationP2;
    delete tryAgainPause;
    delete saveGamePause;
    delete exitPause;
    for(short int i=0;i<points.length();i++)
        delete points[i];
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



//move and collition with players
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape){
        setInPause(getInPause()+1);
        if(getInPause()%2!=0){
            pause->setVisible(true);
            tryAgainPause->setVisible(true);
            saveGamePause->setVisible(true);
            exitPause->setVisible(true);

            for(short int i=0;i<birdEnemies.length();i++)
                birdEnemies[i]->getMove()->stop();

            for(short int i=0;i<scorpionEnemies.length();i++)
                scorpionEnemies[i]->getFire()->stop();

            moving->stop();
            clock->getIncrease()->stop();
        }
        else{
            pause->setVisible(false);
            tryAgainPause->setVisible(false);
            saveGamePause->setVisible(false);
            exitPause->setVisible(false);

            for(short int i=0;i<birdEnemies.length();i++)
                birdEnemies[i]->getMove()->start();

            for(short int i=0;i<scorpionEnemies.length();i++)
                scorpionEnemies[i]->getFire()->start();

            if(getDifficulty()=="Easy")
                moving->start(50);
            else if(getDifficulty()=="Normal")
                moving->start(40);
            else if(getDifficulty()=="Hard")
                moving->start(30);
            clock->getIncrease()->start(1000);
        }

    }
    if(getInPause()%2==0){
        for(short int i=0;i<players.length();i++){
            players[i]->walk(event->key());
        }

        for(short int I=0;I<players.length();I++)
            for(short int i=0;i<solidBlocks.length();i++)
                if(abs(solidBlocks[i]->x()-players[I]->x())<40 and abs(solidBlocks[i]->y()-players[I]->y())<=40)
                    solidBlocks[i]->collidingInMove(event->key());          
    }

}

void MainWindow::startGame()
{
    //Size window
    this->setGeometry(0,20,1924,1000);

    //scene
    scene = new QGraphicsScene;
    scene->setBackgroundBrush(QBrush(QImage(":/sprites/MapGame.jpeg")));
    //scene->setSceneRect(getScenePosX(),getScenePosY(),ui->graphicsView->width(),ui->graphicsView->height());
    //-----------------------------------------------------------------

    //create QGraphicsView
    view = new QGraphicsView(scene,this);
    view->setGeometry(0,0,1920,1080);
    view->show();
    //---------------------------------------

    //players
    for(short int i=0;i<players.length();i++)
        scene->addItem(players[i]);
    //----------------------------------------

    //Map and enemies
    createMap();
    createEnemies();
    //----------------------------------------

    //extras
    scene->addItem(clock);
    scene->addItem(scoreP1);
    scene->addItem(scoreP2);
    clock->setPos(0,0);
    scoreP1->setPos(200,0);
    scoreP2->setPos(600,0);
    decorativeObject =  new QGraphicsEllipseItem(0,0,20,20);
    decorativeObject->setPos(players[0]->x(),players[0]->y());
    scene->addItem(decorativeObject);

    finish = new finishLine(300,200,":/sprites/finishLine.png");
    scene->addItem(finish);
    finish->setPos(4400,505);
    //--------------------------------------------------------

    eliminationP1 = new QLabel(this);
    eliminationP1->setVisible(false);
    eliminationP1->setStyleSheet("font: 14pt Rockwell Condensed;"
                            "color: rgb(170, 0, 0);");
    eliminationP1->setGeometry(100,0,220,50);

    eliminationP2 = new QLabel(this);
    eliminationP2->setVisible(false);
    eliminationP2->setStyleSheet("font: 14pt Rockwell Condensed;"
                            "color: rgb(170, 0, 0);");
    eliminationP2->setGeometry(300,0,220,50);

    warning = new QLabel(this);
    warning->setVisible(false);
    warning->setStyleSheet("font: 40pt Rockwell Condensed;"
                            "color: rgb(170, 0, 0);");
    warning->setGeometry(850,50,500,500);

    //pause
    pause = new QLabel(this);
    pause->setVisible(false);
    pause->setText("         PAUSE");
    pause->setGeometry(720,100,350,80);
    pause->setStyleSheet("font: 32pt Pristina;"
                         "color: rgb(255, 255, 255);"
                         "background-color: rgb(0, 0, 0);");

    tryAgainPause = new QPushButton(this);
    tryAgainPause->setVisible(false);
    tryAgainPause->setText("  TRY AGAIN");
    tryAgainPause->setStyleSheet("font: 14pt Pristina;"
                         "color: rgb(255, 255, 255);"
                         "background-color: rgb(0, 0, 0);");
    tryAgainPause->setGeometry(780,200,220,50);

    saveGamePause = new QPushButton(this);
    saveGamePause->setVisible(false);
    saveGamePause->setText("  SAVE GAME");
    saveGamePause->setStyleSheet("font: 14pt Pristina;"
                         "color: rgb(255, 255, 255);"
                         "background-color: rgb(0, 0, 0);");
    saveGamePause->setGeometry(780,280,220,50);

    exitPause = new QPushButton(this);
    exitPause->setVisible(false);
    exitPause->setText("  EXIT");
    exitPause->setStyleSheet("font: 14pt Pristina;"
                         "color: rgb(255, 255, 255);"
                         "background-color: rgb(0, 0, 0);");
    exitPause->setGeometry(780,360,220,50);
    //--------------------------------------------------------

    //music
    musicInGame = new QMediaPlayer;
    musicInGame->setMedia(QUrl("qrc:/sprites/MainSound.mp3"));
    //musicInGame->play();

    victory = new QMediaPlayer;
    victory->setMedia(QUrl("qrc:/sprites/victory.mp3"));
    //-------------------------------------------------------

    //connect and timers
    connect(moving,SIGNAL(timeout()),this,SLOT(move()));
    connect(WorL,SIGNAL(timeout()),this,SLOT(winnerOrLoser()));
    connect(MDO,SIGNAL(timeout()),this,SLOT(moveDecorativeObject()));
    connect(IPS,SIGNAL(timeout()),this,SLOT(increasPoints()));
    connect(tryAgainPause, &QPushButton::clicked, this, &MainWindow::resetGame);
    connect(saveGamePause, &QPushButton::clicked, this, &MainWindow::saveInPause);
    connect(exitPause, &QPushButton::clicked, this, &MainWindow::exitGame);


    if(getDifficulty()=="Easy")
        moving->start(50);
    else if(getDifficulty()=="Normal")
        moving->start(40);
    else if(getDifficulty()=="Hard")
        moving->start(30);
    WorL->start(100);
    MDO->start(10);
    IPS->start(100);
    //-----------------------------------------------------------
}


void MainWindow::createMap()
{
    //first piramides
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
                    //SET POINTS
                    if((col==numRow+numPiramides-row or col==numRow+numPiramides+row) and
                            (x>players[0]->x() and x>players[1]->x())){
                        points.push_back(new point(17,17,":/sprites/point.png"));
                        points.back()->setPos(x+14,y-30);
                    }

                }
            }
    //middle piramide
    for(short int row=0,y=545;row<numRow+2;row++,y+=40)
        for(short int col=0,x=1700;col<numCol+4;x+=40,col++)
            if(col>=numRow+2-row and col<=numRow+2+row ){
                solidBlocks.push_back(new solidBlock(40,40,":/sprites/solidBlock.png"));
                solidBlocks.back()->setPos(x,y);
                if(col==numRow+2-row or col==numRow+2+row){
                    points.push_back(new point(17,17,":/sprites/point.png"));
                    points.back()->setPos(x+14,y-30);
                }
            }

    //last piramides
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
                    if(col==numRow+numPiramides-row or col==numRow+numPiramides+row){
                        points.push_back(new point(17,17,":/sprites/point.png"));
                        points.back()->setPos(x+14,y-30);
                    }
                }
            }

    //add to scene
    for(short int i=0;i<solidBlocks.length();i++){
        solidBlocks[i]->setPtrPlayers(players);
        scene->addItem(solidBlocks[i]);
    }

    for(short int i=0;i<points.length();i++)
        scene->addItem(points[i]);

}

void MainWindow::createEnemies()
{
    //SET BIRD ENEMIES
    for(short int i=0,x=1530;i<2;i++,x+=650){
        birdEnemies.push_back(new bird(70,70,":/sprites/EnemyBird.png",x,300));
        birdEnemies.back()->setPtrPlayers(players);
        scene->addItem(birdEnemies.back());
    }

    //SET SCORPION ENEMIES
    for(short int i=0,x=-120;i<3;i++,x+=360){
        scorpionEnemies.push_back(new scorpion(50,50,":/sprites/scorpion.PNG"));
        scorpionEnemies.back()->setPos(x,655);
        scorpionEnemies.back()->setPtrPlayers(players);
        scene->addItem(scorpionEnemies.back()->getBullet());
        scene->addItem(scorpionEnemies.back());    
    }

    //adjust Vy of third scorpion
    scorpionEnemies.back()->setVy(28);

    //SET MARSH ENEMIES
    for(short int i=0,x=2925;i<2;i++,x+=450){
        marshEnemies.push_back(new marsh(20,200,":/sprites/marsh.png"));
        marshEnemies.back()->setPos(x,695);
        marshEnemies.back()->setPtrPlayers(players);
        scene->addItem(marshEnemies.back());
    }
    for(short int i=0,x=3740;i<3;i++,x+=200){
        marshEnemies.push_back(new marsh(20,200,":/sprites/marsh.png"));
        marshEnemies.back()->setPos(x,695);
        marshEnemies.back()->setPtrPlayers(players);
        scene->addItem(marshEnemies.back());
    }
}

//moving scene and signs
void MainWindow::move()
{
    setScenePosX(getScenePosX()+2);
    clock->setX(getScenePosX()+500);
    scoreP1->setX(getScenePosX()+800);
    scoreP2->setX(getScenePosX()+1300);
    scene->setSceneRect(getScenePosX(),getScenePosY(),view->width()-5,view->height()-5);
}

void MainWindow::increasPoints()
{
    for(short int i=0;i<players.length();i++)
        for(int I=0;I<points.length();I++){
            if(abs(players[i]->x()-points[I]->x())<=17 and abs(players[i]->y()-points[I]->y())<=50){
                delete points[I];
                points.removeAt(I);
                if(i==0)
                    scoreP1->increaseScore();
                else
                    scoreP2->increaseScore();
                break;
            }
        }
}

void MainWindow::winnerOrLoser(){

    for (short int I=0;I<players.length();I++ ){
        //win
        if(players[I]->x()>=finish->x()){
            warning->setVisible(true);
            switch (I) {
                case 0:
                    warning->setText("Player 1 won");
                    break;
                case 1:
                    warning->setText("Player 2 won");
                    break;
            }
            for(short int i=0;i<birdEnemies.length();i++)
                birdEnemies[i]->getMove()->stop();

            for(short int i=0;i<scorpionEnemies.length();i++)
                scorpionEnemies[i]->getFire()->stop();

            moving->stop();
            clock->getIncrease()->stop();
            victory->play();
        }
        //-------------------------------------------------------

        //lose
        if(players[I]->x()<getScenePosX()){
            switch (I) {
                case 0:
                    eliminationP1->setVisible(true);
                    eliminationP1->setText("Player 1 Eliminated");
                    players[0]->setVisible(false);
                    break;
                case 1:
                    eliminationP2->setVisible(true);
                    eliminationP2->setText("Player 2 Eliminated");
                    players[1]->setVisible(false);
                    break;
            }
        }
    }
    if(!players[0]->isVisible() and !players[1]->isVisible()){
        warning->setVisible(true);
        warning->setText("You lost");
        for(short int i=0;i<birdEnemies.length();i++)
            birdEnemies[i]->getMove()->stop();

        for(short int i=0;i<scorpionEnemies.length();i++)
            scorpionEnemies[i]->getFire()->stop();

        moving->stop();
        clock->getIncrease()->stop();
    }
    //-----------------------------------------------------------

}

//uniform circular motion
void MainWindow::moveDecorativeObject()
{
    setAngle(getAngle()+1);
    decorativeObject->setPos(15+players[0]->x()+35*sin(getAngle()*3.1416/180),35+players[0]->y()+54*cos(getAngle()*3.1416/180));
}

//other funtions
//----------------------------------------------------------------------------------------------------------------------
QString MainWindow::intToStr(int number)
{
    QString str="",str2="";
    int number2=0,i=0;

    if(number<0){
        number*=-1;
        str2[i++]='-';
    }

    while(number!=0){
        number2=number/10;
        number2 = number-(number2*10);
        str[i++]=number2+48;
        number/=10;
    }

    for(int i=str.length();i>0;i--)
        str2[i]=str[str.length()-i];

    return str2;
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

QString MainWindow::getDifficulty() const
{
    return difficulty;
}

void MainWindow::setDifficulty(const QString &value)
{
    difficulty = value;
}

int MainWindow::getInPause() const
{
    return inPause;
}

void MainWindow::setInPause(int value)
{
    inPause = value;
}

QString MainWindow::getCurrentlyGame() const
{
    return currentlyGame;
}

void MainWindow::setCurrentlyGame(const QString &value)
{
    currentlyGame = value;
}

QString MainWindow::getCurrentlyGameP2() const
{
    return currentlyGameP2;
}

void MainWindow::setCurrentlyGameP2(const QString &value)
{
    currentlyGameP2 = value;
}

int MainWindow::getAngle() const
{
    return Angle;
}

void MainWindow::setAngle(int value)
{
    Angle = value;
}
//---------------------------------------------------------------------------------------------------------------------

//clear screen
//delete all but one botton ,label and background
void MainWindow::deleteMenu()
{
    ui->verticalLayout->deleteLater();
    ui->pushButton->deleteLater();
    ui->pushButton_3->deleteLater();
    ui->pushButton_4->deleteLater();
}

void MainWindow::deleteNewGame()
{
    delete saveInMenu;
    delete comboBox;
    delete label_4;
    delete label_3;
    delete ui->label_2;
    delete ui->label;
    delete textEdit2;
    delete textEdit1;
}

void MainWindow::deleteLoadGame()
{
    delete comboBox;
    delete load;
    delete ui->label;
}
//----------------------------------------------------------------------------------------------------------------------

//Menu

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

    saveInMenu->setVisible(true);
    saveInMenu->setGeometry(220,480,300,50);
    saveInMenu->setText("Start");
    saveInMenu->setStyleSheet("font: 28pt Stencil");

}

//save new game
void MainWindow::saveNewGame()
{
    if(textEdit1->toPlainText()==0)
        textEdit1->setPlaceholderText("This field can't be empty");

    if(textEdit2->toPlainText()==0)
        textEdit2->setPlaceholderText("This field can't be empty");

    else{  
        QFile file("../Proyectofinal2022/DB/games.txt");
        if (!file.open(QIODevice::ReadOnly |QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream read(&file);
        bool duplicateName1=false,duplicateName2=false;
        QString line = read.readLine();


        while(!line.isEmpty()){
            if(textEdit1->toPlainText()==line){
                duplicateName1=true;
                break;
            }
            line = read.readLine();
        }

        if(duplicateName1){
            textEdit1->clear();
            textEdit1->setPlaceholderText(line+" already exist");
        }

        read.reset();
        line = read.readLine();
        while(!line.isEmpty()){
            if(textEdit2->toPlainText()==line){
                duplicateName2=true;
                break;
            }
            line = read.readLine();
        }

        if(duplicateName2){
            textEdit2->clear();
            textEdit2->setPlaceholderText(line+" already exist");
        }

        if(!duplicateName1 and !duplicateName2){
            QTextStream write(&file);
            //player 1
            write<<textEdit1->toPlainText()<<'\n'<<"-400,625,625,0,"<<comboBox->currentText()<<'\n';
            //player 2 only has its positions
            write<<textEdit2->toPlainText()<<'\n'<<"-390,625,625"<<'\n';
            setCurrentlyGame(textEdit1->toPlainText());
            setCurrentlyGameP2(textEdit2->toPlainText());
            setDifficulty(comboBox->currentText());

            deleteNewGame();
            players[0]->setPos(-400,625);
            players[1]->setPos(-390,625);
            startGame();
        }
    }
}

//load game in menu
void MainWindow::on_pushButton_4_clicked()
{
    deleteMenu();

    QFile file("../Proyectofinal2022/DB/games.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream read(&file);
    QString line = read.readLine();


    //Only read player1's name
    while (!line.isNull()) {
        comboBox->addItem(line);
        //Statistics player 1
        line = read.readLine();
        //name player 2
        read.readLine();
        //Statistics player 2
        line = read.readLine();
        //name player 1
        line = read.readLine();
    }

    comboBox->setVisible(true);
    comboBox->setGeometry(250,150,300,30);

    load->setVisible(true);
    load->setGeometry(250,200,300,50);
    load->setStyleSheet("font: 28pt Stencil;"
                        "border-image: url(:/sprites/Botons.png);");
    load->setText("Load");
}

//load selected game
void MainWindow::LoadGame()
{
    QFile file("../Proyectofinal2022/DB/games.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QList<QString> statistics;
    QTextStream read(&file);

    QString line = read.readLine();
    while (!line.isNull()) {
        if(comboBox->currentText()==line){
            //statistics player 1
            setCurrentlyGame(comboBox->currentText());
            line = read.readLine();
            statistics = line.split(',');
            players[0]->setPos(statistics[0].toInt(),statistics[1].toInt()-20);
            players[0]->setFloor(statistics[2].toInt());
            clock->setNumber(statistics[3].toInt());
            scoreP1->setNumber(statistics[4].toInt());
            scoreP1->updateSign(statistics[4].toInt());
            setDifficulty(statistics[5]);
            //name player2
            line = read.readLine();
            setCurrentlyGameP2(line);
            //statistics player 2
            line = read.readLine();
            statistics = line.split(',');
            players[1]->setPos(statistics[0].toInt(),statistics[1].toInt()-20);
            players[1]->setFloor(statistics[2].toInt());
            scoreP2->setNumber(statistics[3].toInt());
            scoreP2->updateSign(statistics[3].toInt());
            deleteLoadGame();
            startGame();
            break;
        }
        //statistics player 1
        read.readLine();
        //name player 2
        read.readLine();
        //statistics player 2
        read.readLine();
        //name player 1
        line = read.readLine();
    }
}

//reset game
void MainWindow::resetGame()
{
    for(int i=points.length();i>0;i--){
        delete points[0];
        points.removeAt(0);
    }
    //SET POINTS AGAIN
    for (short int numPiramides=0;numPiramides<3;numPiramides++)
        for(short int row=0,y=625-(40*numPiramides);row<numRow+numPiramides;row++,y+=40)
            for(short int col=0,x=0;col<numCol+(numRow+numPiramides)*2;x+=40,col++){
                if(col==0){
                    if(numPiramides==0)
                        x-=80;
                    for(short int i=0,inc=1;i<numPiramides;i++,inc-=2)
                        x+=80*numPiramides+inc+200;
                }
                if(col==numRow+numPiramides-row or col==numRow+numPiramides+row){
                    points.push_back(new point(17,17,":/sprites/point.png"));
                    points.back()->setPos(x+14,y-30);
                }

            }
    //----------------------------------------------------------------------------------

    //middle points
    for(short int row=0,y=545;row<numRow+2;row++,y+=40)
        for(short int col=0,x=1700;col<numCol+4;x+=40,col++)
            if(col==numRow+2-row or col==numRow+2+row){
                points.push_back(new point(10,10,":/sprites/point.png"));
                points.back()->setPos(x+14,y-30);
            }
    //----------------------------------------------------------------------------------


    //last points
    for (short int numPiramides=2;numPiramides>=0;numPiramides--)
        for(short int row=0,y=625-(40*numPiramides);row<numRow+numPiramides;row++,y+=40)
            for(short int col=0,x=3500;col<numCol+(numRow+numPiramides)*2;x+=40,col++){
                if(col==0){
                    if(numPiramides==0)
                        x+=80;
                    for(short int i=0,inc=1;i<numPiramides;i++,inc-=2)
                        x-=80*numPiramides+inc+300;
                }
                if(col==numRow+numPiramides-row or col==numRow+numPiramides+row){
                    points.push_back(new point(10,10,":/sprites/point.png"));
                    points.back()->setPos(x+14,y-30);
                }
            }
    //-----------------------------------------------------------------------------------

    //add to scene
    for(short int i=0;i<points.length();i++)
        scene->addItem(points[i]);

    scoreP1->setNumber(0);
    scoreP1->updateSign(0);
    scoreP2->setNumber(0);
    scoreP2->updateSign(0);
    eliminationP1->setVisible(false);
    eliminationP2->setVisible(false);
    warning->setVisible(false);
    players[0]->setVisible(true);
    players[1]->setVisible(true);
    players[0]->setPos(-400,625);
    players[1]->setPos(-380,625);
    setScenePosX(-500);
    clock->setX(0);
    clock->setNumber(0);
    //----------------------------------------------------------------------------------
}

void MainWindow::saveInPause()
{
    QFile file("../Proyectofinal2022/DB/games.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QString dataGame = "";

    QTextStream read(&file);
    QString line = read.readLine();
    while (!line.isNull()) {
        if(line==getCurrentlyGame()){        
            dataGame+=getCurrentlyGame()+'\n';
            dataGame+=intToStr(players[0]->x()).remove(' ');
            dataGame+=",";
            dataGame+=intToStr(players[0]->y()).remove(' ');
            dataGame+=",";
            dataGame+=intToStr(players[0]->getFloor()).remove(' ');
            dataGame+=",";
            dataGame+=intToStr(clock->getNumber()).remove(' ');
            dataGame+=",";
            dataGame+=intToStr(scoreP1->getNumber()).remove(' ');
            dataGame+=",";
            dataGame+=getDifficulty()+"\n";
            dataGame+=getCurrentlyGameP2()+"\n";
            dataGame+=intToStr(players[1]->x()).remove(' ');
            dataGame+=",";
            dataGame+=intToStr(players[1]->y()).remove(' ');
            dataGame+=",";
            dataGame+=intToStr(players[1]->getFloor()).remove(' ');
            dataGame+=",";
            dataGame+=intToStr(scoreP2->getNumber()).remove(' ');
            dataGame+=+"\n";
            read.readLine();
            read.readLine();
            read.readLine();
        }
        else
            dataGame += line+'\n';
        line = read.readLine();
    }
    file.remove();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream write(&file);

    write<<dataGame;
    file.close();
}

void MainWindow::exitGame()
{
    this->close();
}

//delete game
void MainWindow::on_pushButton_3_clicked()
{
    on_pushButton_4_clicked();
    load->setText("Delete Game");
    disconnect(load, &QPushButton::clicked, this, &MainWindow::LoadGame);
    connect(load, &QPushButton::clicked, this, &MainWindow::deleteGame);
}

void MainWindow::deleteGame()
{
    QFile file("../Proyectofinal2022/DB/games.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QString dataGame = "";

    QTextStream read(&file);
    QString line = read.readLine();
    while (!line.isNull()) {
        if(line==comboBox->currentText()){
            read.readLine();
            read.readLine();
            read.readLine();
        }
        else
            dataGame += line+'\n';
        line = read.readLine();
    }
    file.remove();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream write(&file);

    write<<dataGame;
    file.close();
    deleteLoadGame();
    this->close();
}



