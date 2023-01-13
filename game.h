#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QMediaPlayer>
#include <QLabel>
#include "tronplayer.h"


class Game : public QGraphicsView
{
public:
    Game(int pos, int difficulty);
    void keyPressEvent(QKeyEvent *event);
    void addTronTrail(int playerNumber, int x1, int y1, int x2, int y2);
    QGraphicsScene scene;
    int countdown;
private:
    TronPlayer m_player1;
    TronPlayer m_player2;
    QTimer m_timer;
    QTimer *m_timercountdown;
    QMediaPlayer * m_music;
    QLabel *m_countdownLabel;
    void updateCountdown();
};

#endif // GAME_H
