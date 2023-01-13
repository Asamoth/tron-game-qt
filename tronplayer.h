#ifndef TRONPLAYER_H
#define TRONPLAYER_H

#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QDebug>

#include "trontrail.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class TronPlayer :  public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    TronPlayer(int playerNumber, int startX, int startY, int difficulty);
    ~TronPlayer();
    void keyPressEvent(QKeyEvent *event) override;
    int scorePlayer;
public slots:
    void advanceTronPlayer() ;
private:
    int m_startX;
    int m_startY;
    int m_playerNumber;
    int m_speed;
    int m_dx;
    int m_dy;
    bool m_paused;
    int m_lastPosX;
    int m_lastPosY;
    int m_turningCoords;
    bool m_turning;
    bool m_turningCounter;
    int m_lastOrientation; //0 -> Right ; 1 -> Left ; 2 -> Up ; 3 -> Down
    QGraphicsTextItem *m_scoreText;
    TronTrail *m_trail;
};

#endif // TRONPLAYER_H
