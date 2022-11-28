#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QMediaPlayer>

#include "player.h"
//#include "bonus.h"
#include "score.h"

class Game : public QGraphicsView
{
public:
    Game(int,int,QWidget * parent=0); //par défaut, il n'y a pas de parent

    QGraphicsScene * scene;
    QMediaPlayer * music;
    Player * player1;
    //Player * player2;
    //Bonus * bonus;
    Score * score;
    void gameWindow();
    void settingsWindow();
    //void start(int);
    //void stop();
private:
    int * m_height;
    int * m_width;
    QTimer * m_Timer;
};

#endif // GAME_H
