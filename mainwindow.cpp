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

    warning = new QLabel(this);
    warning->setVisible(false);

    //player
    players.push_back(new player(80,50,":/sprites/player1.png",1));
    players.push_back(new player(80,50,":/sprites/player2.png",2));

    clock = new ownClock("TIME: ",0);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::saveNewGame);
    connect(load, &QPushButton::clicked, this, &MainWindow::LoadGame);
}

MainWindow::~MainWindow()
{
    delete pause;
    delete tryAgainPause;
    delete saveGamePause;
    delete exitPause;
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

            moving->stop();
            clock->getIncrease()->stop();
        }
        else{
            pause->setVisible(false);
            tryAgainPause->setVisible(false);
            saveGamePause->setVisible(false);
            exitPause->setVisible(false);

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

    //create QGraphicsView
    view = new QGraphicsView(scene,this);
    view->setGeometry(0,0,1920,1080);
    view->show();

    //players
    for(short int i=0;i<players.length();i++)
        scene->addItem(players[i]);

    //Map and enemies
    createMap();
    createEnemies();

    //extras
    scene->addItem(clock);
    clock->setPos(0,0);

    finish = new finishLine(300,200,":/sprites/finishLine.png");
    scene->addItem(finish);
    finish->setPos(4700,505);


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

    //connect and timers
    connect(moving,SIGNAL(timeout()),this,SLOT(move()));
    //connect(WorL,SIGNAL(timeout()),this,SLOT(winnerOrLoser()));
    connect(tryAgainPause, &QPushButton::clicked, this, &MainWindow::resetGame);
    connect(saveGamePause, &QPushButton::clicked, this, &MainWindow::saveInPause);

    if(getDifficulty()=="Easy")
        moving->start(50);
    else if(getDifficulty()=="Normal")
        moving->start(40);
    else if(getDifficulty()=="Hard")
        moving->start(30);
    //WorL->start(1000);
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
                }
            }

    //middle piramide
    for(short int row=0,y=545;row<numRow+2;row++,y+=40)
        for(short int col=0,x=1700;col<numCol+4;x+=40,col++)
            if(col>=numRow+2-row and col<=numRow+2+row ){
                solidBlocks.push_back(new solidBlock(40,40,":/sprites/solidBlock.png"));
                solidBlocks.back()->setPos(x,y);
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
                }
            }

    //add to scene
    for(short int i=0;i<solidBlocks.length();i++){
        solidBlocks[i]->setPtrPlayers(players);
        scene->addItem(solidBlocks[i]);
    }

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
    scene->setSceneRect(getScenePosX(),getScenePosY(),view->width()-5,view->height()-5);
}

void MainWindow::winnerOrLoser(){
    /*
    for (short int I=0;I<players.length();I++ ){
        if(players[I]->x()>=finish->x())
            switch (players[I]->getNumberPlayer()) {
                case 1:
                    //winner = new QLabel("player 1 winner",this);
                    break;
                case 2:
                    //winner = new QLabel("player 2 winner",this);
                    break;
            }
        else if(players[I]->x()<getScenePosX())
            switch (players[I]->getNumberPlayer()) {
                case 1:
                    //winner = new QLabel("player 1 lost",this);
                    break;
                case 2:
                    //winner = new QLabel("player 2 lost",this);
                    break;
            }
    }
*/
}

//other funtions
//----------------------------------------------------------------------------------------------------------------------

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

//clear screen
//----------------------------------------------------------------------------------------------------------------------

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
    delete ui->pushButton_2;
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

//Menu
//----------------------------------------------------------------------------------------------------------------------

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
            write<<textEdit1->toPlainText()<<'\n'<<"-400,625,0,"<<comboBox->currentText()<<'\n';
            //player 2 only has its positions
            write<<textEdit2->toPlainText()<<'\n'<<"-390,625"<<'\n';
            setCurrentlyGame(textEdit1->toPlainText());
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
    ui->pushButton_2->deleteLater();

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
            players[0]->setPos(statistics[0].toInt(nullptr,10),statistics[1].toInt(nullptr,10));
            clock->setNumber(statistics[2].toInt(nullptr,10));
            setDifficulty(statistics[3]);
            //name player2
            read.readLine();
            //statistics player 2
            line = read.readLine();
            statistics = line.split(',');
            players[1]->setPos(statistics[0].toInt(nullptr,10),statistics[1].toInt(nullptr,10));
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
    players[0]->setPos(-400,625);
    players[1]->setPos(-380,625);
    setScenePosX(-500);
    clock->setX(0);
    clock->setNumber(0);
}

void MainWindow::saveInPause()
{
    /*QFile file("../Proyectofinal2022/DB/games.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QString dataGame = "";

    QTextStream read(&file);
    QString line = read.readLine();
    while (!line.isNull()) {
        dataGame += line;
    }

    //QTextStream write(&file);


    file.remove();


    file.close();*/

}
