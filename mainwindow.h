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

#include "player.h"
#include "solidblock.h"
#include "bird.h"
#include "scorpion.h"
#include "marsh.h"
#include "ownclock.h"
#include "finishline.h"

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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    int scenePosX=-500,scenePosY=0;
    int inPause=0;

    //extras
    ownClock *clock;
    finishLine *finish;
    QString difficulty="";

    //menu
    QPlainTextEdit *textEdit1;
    QPlainTextEdit *textEdit2;
    QComboBox *comboBox;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *warning;
    QPushButton *load;

    //pause
    QLabel *pause;
    QPushButton *tryAgainPause;
    QPushButton *saveGamePause;
    QPushButton *exitPause;

    //Lists
    QList<player*> players;
    QList<scorpion*> scorpionEnemies;
    QList<bird*> birdEnemies;
    QList<marsh*> marshEnemies;
    QList<solidBlock*> solidBlocks;

    //timers
    QTimer *moving = new QTimer;
    QTimer *WorL = new QTimer;


public slots:
    void move();
    void saveNewGame();
    void winnerOrLoser();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
};
#endif // MAINWINDOW_H
