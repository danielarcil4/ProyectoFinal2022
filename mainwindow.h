#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QTimer>
#include <QGraphicsView>
#include <QPlainTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QMediaPlayer>

#include "player.h"
#include "solidblock.h"
#include "bird.h"
#include "scorpion.h"
#include "marsh.h"
#include "ownclock.h"
#include "finishline.h"
#include "score.h"
#include "point.h"

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

    //game
    void keyPressEvent(QKeyEvent *event);
    void startGame();
    void LoadGame();
    void resetGame();
    void saveInPause();
    void exitGame();
    void deleteGame();
    QString intToStr(int);

    //create
    void createMap();
    void createEnemies();

    //delete
    void deleteLoadGame();
    void deleteNewGame();
    void deleteMenu();

    //others funtions
    int getScenePosX() const;
    void setScenePosX(int value);

    int getScenePosY() const;
    void setScenePosY(int value);

    QString getDifficulty() const;
    void setDifficulty(const QString &value);

    int getInPause() const;
    void setInPause(int value);

    QString getCurrentlyGame() const;
    void setCurrentlyGame(const QString &value);

    QString getCurrentlyGameP2() const;
    void setCurrentlyGameP2(const QString &value);

    int getAngle() const;
    void setAngle(int value);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    int scenePosX=-500,scenePosY=0;
    int inPause=0;
    int Angle=0;

    //extras
    score *scoreP1;
    score *scoreP2;
    ownClock *clock;
    finishLine *finish;
    QString difficulty="";
    QString currentlyGame="",currentlyGameP2="";
    QGraphicsEllipseItem *decorativeObject;

    //menu
    QPlainTextEdit *textEdit1;
    QPlainTextEdit *textEdit2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *eliminationP1;
    QLabel *eliminationP2;
    QLabel *warning;
    QPushButton *load;
    QComboBox *comboBox;

    //Pause
    QLabel *pause;
    QPushButton *saveInMenu;
    QPushButton *tryAgainPause;
    QPushButton *saveGamePause;
    QPushButton *exitPause;

    //Lists
    QList<player*> players;
    QList<scorpion*> scorpionEnemies;
    QList<bird*> birdEnemies;
    QList<marsh*> marshEnemies;
    QList<solidBlock*> solidBlocks;
    QList<point*> points;

    //Timers
    QTimer *moving = new QTimer;
    QTimer *WorL = new QTimer;
    QTimer *MDO = new QTimer;
    QTimer *IPS = new QTimer;

    //Sounds
    QMediaPlayer *musicInGame;

public slots:
    void move();
    void increasPoints();
    void saveNewGame();
    void winnerOrLoser();
    void moveDecorativeObject();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
};
#endif // MAINWINDOW_H
