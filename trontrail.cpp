#include "trontrail.h"
#include "qpen.h"

/*
 * La classe TronTrail est une sous-classe de QGraphicsLineItem qui est utilisée pour représenter les trainées
 * laissées par les objets TronPlayer dans le jeu. Il est nécessaire de différencier les traces de différents
 * joueurs car elles peuvent entrer en collision et il est alors nécessaire de pouvoir différencier les trainées
 * de chaque joueur avec leur numéro de joueur. La classe TronTrail ajoute une variable de membre playerNumber qui
 * stocke le numéro de joueur de l'objet TronPlayer qui a créé la trainée, ça nous permet d'identifier les trainées
 * de quel joueur nous avons à faire et de vérifier les collisions avec les traces d'autres joueurs.
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

