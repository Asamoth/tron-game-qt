#include "trontrail.h"
#include "qpen.h"

/*
  * The TronTrail class is a subclass of QGraphicsLineItem which is used to represent trails
  * left by TronPlayer objects in the game. It is necessary to differentiate the traces of different
  * players because they can collide and it is then necessary to be able to differentiate the trails
  * of each player with their player number. The TronTrail class adds a member variable playerNumber which
  * stores the player number of the TronPlayer object that created the trail, it allows us to identify trails
  * which player we have to do and check collisions with other player's tracks.
*/
TronTrail::TronTrail(int playerNumber, qreal initialX, qreal initialY, qreal finalX, qreal finalY, QGraphicsItem *parent)
    : QGraphicsLineItem(initialX, initialY, finalX, finalY, parent),
      m_playerNumber(playerNumber)
{
    QPen pen = this->pen();
    pen.setWidth(10);
    this->setPen(pen);
}
int TronTrail::playerNumber() const
{
    return m_playerNumber;
}

