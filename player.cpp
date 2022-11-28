#include "player.h"
#include "game.h"

#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <QDebug>
#include <QGraphicsRectItem>

extern Game * game; // Il y a un objet externe global s'appelant game

Player::Player(int profile, int PLAYERHEIGHT, int PLAYERWIDTH, int PLAYERSPEED, int CANVASWIDTH, int CANVASHEIGHT, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    // on définit le son que le joueur fera en utilisant un bonus
    pickUpBonus = new QMediaPlayer();
    pickUpBonus->setMedia(QUrl("qrc:/sounds/collect-item-bonus.wav"));

    // on initialise la taille des joueurs, leur vitesse ainsi que le profile du joueur (joueur 1 ou joueur 2)
    playerHeight = PLAYERHEIGHT;
    playerWidth = PLAYERWIDTH;
    playerProfile = profile;
    playerSpeed = PLAYERSPEED;
    canvasWidth = CANVASWIDTH;
    canvasHeight = CANVASHEIGHT;
    /*
    newPos va servir afin de savoir si l'avatar a tourné ou non à l'itération précédente.
    Si l'avatar change de direction à cette itération, celui-ci ne va pas se déplacer.
    Ainsi, l'avatar n'obtiens pas de nouvelle position, d'où newPos sera false.
    Sinon newPos sera true lorsque l'avatar avance tout droit dans une direciton.
    On en a besoin pour la fonction trail(), où l'avatar laisse une trainée derrière lui.
    En effet, il ne faut pas que l'on fasse apparaître de trainée si l'avatar ne se déplace pas.
    */
    newPos = true;

    if (playerProfile == 1)
    {
        // on définit la représentation graphique du joueur en fonction de son profile
        setPixmap(QPixmap(":/images/bTronS.png"));
        // on initialise la direction du joueur
        lastKey = Qt::Key_Right;
        lastOrientation.append(false);
        lastOrientation.append(false);
        lastOrientation.append(false);
        lastOrientation.append(true);
    }
    else
    {
        setPixmap(QPixmap(":/images/yTronS.png"));
        lastKey = Qt::Key_Left;
    }
    /*
    Afin de définir une vitesse de déplacement pour les avatars des joueurs qui doivent se déplacer de manière
    automatique, il s'agit de définir une période selon laquelle on va rappeler la fonction de déplacement des joueurs
    qui définit elle-même une distance de déplacement en pixels selon la direction choisie.
    */
    Timer = new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(movePlayer()));
    connect(Timer,SIGNAL(timeout()),this,SLOT(trail()));
    // on démarre le timer
    Timer->start(50);
}

/*
Cette fonction a pour objectif de definir la direction de l'avatar du joueur en fonction de la touche appuyée.
Sachant que cet avatar se déplace automatiquement, il faut une fonction qui va permettre de modifier et de
garder en mémoire un entier correspondant à une touche pressée. Celle-ci représentant la prochaine direction
que prendra l'avatar lors de son déplacement automatique.
*/
void Player::keyPressEvent(QKeyEvent *event)
{
    // les touches à presser sont différentes en fonciton du profile du joueur
    if (playerProfile == 1)
    {
        // si l'utilisateur appuie sur la flêche gauche
        if (event->key() == Qt::Key_Left)
        {
            // on empêche le joueur de revenir sur ses pas car il laisse une trainée dernière lui qui entraînerait une collision
            if (lastKey != Qt::Key_Right)
            {
                lastKey = Qt::Key_Left;
            }

        }
        else if (event->key() == Qt::Key_Right)
        {
            if (lastKey != Qt::Key_Left)
            {
                lastKey = Qt::Key_Right;
            }
        }
        else if (event->key() == Qt::Key_Up)
        {
            if (lastKey != Qt::Key_Down)
            {
                lastKey = Qt::Key_Up;
            }
        }
        else if (event->key() == Qt::Key_Down)
        {
            if (lastKey != Qt::Key_Up)
            {
                lastKey = Qt::Key_Down;
            }
        }
        // press L to use item for player 1
        else if (event->key() == Qt::Key_L)
        {
            // create a bonus object
//            Bullet * bullet = new Bullet();
//            bullet->setPos(x()+45,y());
//            scene()->addItem(bullet);

            // play item sound
            if (pickUpBonus->state() == QMediaPlayer::PlayingState){
                pickUpBonus->setPosition(0);
            }
            else if (pickUpBonus->state() == QMediaPlayer::StoppedState){
                pickUpBonus->play();
            }
        }
    }
    else
    {
        if (event->key() == Qt::Key_A)
        {
            if (lastKey != Qt::Key_D)
            {
                lastKey = Qt::Key_A;
            }
        }
        else if (event->key() == Qt::Key_D)
        {
            if (lastKey != Qt::Key_A)
            {
                lastKey = Qt::Key_D;
            }
        }
        else if (event->key() == Qt::Key_W)
        {
            if (lastKey != Qt::Key_S)
            {
                lastKey = Qt::Key_W;
            }
        }
        else if (event->key() == Qt::Key_S)
        {
            if (lastKey != Qt::Key_W)
            {
                lastKey = Qt::Key_S;
            }
        }
        // press E to use item
        else if (event->key() == Qt::Key_E)
        {
            // create a bonus object
//            Bonus * bonus = new Bonus();
//            bonus->setPos(x()+45,y());
//            scene()->addItem(bonus);

            // play item sound
            if (pickUpBonus->state() == QMediaPlayer::PlayingState){
                pickUpBonus->setPosition(0);
            }
            else if (pickUpBonus->state() == QMediaPlayer::StoppedState){
                pickUpBonus->play();
            }
        }
    }
}

void Player::endCondition()
{
    qDebug() << "game over";
    Timer->stop();
    //game->music->stop();
    game->scene->removeItem(this);
    delete this;
    //playerProfile = 0;
    //game->stop();
}

/*
Etant donnée que le déplacement se fait automatiquement, il faut donc une fonction qui va être appelée périodiquement
et qui va faire se déplacer l'avatar en fonction de la dernière direction pressée.
*/
void Player::movePlayer()
{
    /*
    On enregistre la position actuelle du joueur dans la QList avant de modifier la position du joueur en fonction de
    sa dernière direction pressée. Ainsi la Qlist garde en mémoire la dernière position occupée, ce qui va nous permettre
    d'y créer un objet (afin d'être détectable pour les collisions) pour représenter la trainée.
    */

    lastPosx = x();
    lastPosy = y();

    //QList<QGraphicsItem *> colliding_items = collidingItems();
    //qDebug() << collidingItems() << " collisions " ;


    //lastOrientation est [Up,Down,Left,Right]
    if (playerProfile == 1)
    {
        qDebug() << lastOrientation;
        if (lastKey == Qt::Key_Up)
        {
            // on vérifie que le joueur est à l'intérieur du canvas
            if (pos().y() > 0)
            {
                if (lastOrientation[3] == true) //Right -> Up
                {
                    /*
                    On veut que l'image de l'avatar du joueur pivote lorsque celui-ci change de direction,
                    pour ce faire, on définit le point duquel la rotation de l'image se fera : ici vers l'arrière
                    la moto, puis, on pivote cette image dans la direction désirée.
                    */
                    //setTransformOriginPoint(1/5 * playerHeight,1/2 * playerWidth);
                    this->setRotation(-90);
                    //l'angle représente l'angle que doit avoir l'avatar dans sa nouvelle position par rapport à l'horizontale

                    // On mets à jour lastOrientation pour la prochaine itération.
                    lastOrientation.clear();
                    lastOrientation.append(true);
                    lastOrientation.append(false);
                    lastOrientation.append(false);
                    lastOrientation.append(false);

                    //L'avatar ne change pas de position, il tourne.
                    newPos = false;
                }
                else if (lastOrientation[2] == true) //Left -> Up
                {
                    //setTransformOriginPoint(4/5 * playerHeight,1/2 * playerWidth);
                    this->setRotation(-90);
                    lastOrientation.clear();
                    lastOrientation.append(true);
                    lastOrientation.append(false);
                    lastOrientation.append(false);
                    lastOrientation.append(false);

                    newPos = false;
                }
                /*
                Si l'orientation précédente de l'avatar n'est ni vers la droite, ni la gauche, alors l'avatar va nécessairement tout
                droit dans la direction donnée par lastKey, car l'avatar ne peut pas basculer de haut en bas, soit faire une rotation de 180°.
                */
                else
                {
                    setPos(x(),y() - playerSpeed);
                    newPos = true;
                }
            }
            else
            {
                endCondition();
            }
        }
        else if (lastKey == Qt::Key_Down)
        {
            if (pos().y() + playerHeight < canvasHeight)
            {
                if (lastOrientation[2] == true) // Left -> Down
                {
                    //setTransformOriginPoint(4/5 * playerHeight,1/2 * playerWidth);
                    this->setRotation(90);
                    lastOrientation.clear();
                    lastOrientation.append(false);
                    lastOrientation.append(true);
                    lastOrientation.append(false);
                    lastOrientation.append(false);

                    newPos = false;
                }
                else if (lastOrientation[3] == true) // Right -> Down
                {
                    //setTransformOriginPoint(1/5 * playerHeight,1/2 * playerWidth);
                    this->setRotation(90);
                    lastOrientation.clear();
                    lastOrientation.append(false);
                    lastOrientation.append(true);
                    lastOrientation.append(false);
                    lastOrientation.append(false);

                    newPos = false;
                }
                else
                {
                    setPos(x(),y() + playerSpeed);
                    newPos = true;
                }
            }
            else
            {
                endCondition();
            }
        }
        else if (lastKey == Qt::Key_Left)
        {
            if (pos().x() > 0)
            {
                if (lastOrientation[0] == true) // Up -> left
                {
                    //setTransformOriginPoint(1/2 * playerHeight,4/5 * playerWidth);
                    this->setRotation(-180);
                    lastOrientation.clear();
                    lastOrientation.append(false);
                    lastOrientation.append(false);
                    lastOrientation.append(true);
                    lastOrientation.append(false);

                    newPos = false;
                }
                else if (lastOrientation[1] == true) // Down -> left
                {
                    //setTransformOriginPoint(1/2 * playerHeight,1/5 * playerWidth);
                    this->setRotation(-180);
                    lastOrientation.clear();
                    lastOrientation.append(false);
                    lastOrientation.append(false);
                    lastOrientation.append(true);
                    lastOrientation.append(false);

                    newPos = false;
                }
                else
                {
                    setPos(x()-playerSpeed,y());
                    newPos = true;
                }
            }
            else
            {
                endCondition();
            }
        }
        else if (lastKey == Qt::Key_Right)
        {
            if (pos().x() + playerHeight < canvasWidth)
            {
                setPos(x() + playerSpeed,y());
                if (lastOrientation[0] == true) // Up -> right
                {
                    //setTransformOriginPoint(1/2 * playerHeight,4/5 * playerWidth);
                    this->setRotation(0);
                    lastOrientation.clear();
                    lastOrientation.append(false);
                    lastOrientation.append(false);
                    lastOrientation.append(false);
                    lastOrientation.append(true);

                    newPos = false;
                }
                else if (lastOrientation[1] == true) // Down -> right
                {
                    //setTransformOriginPoint(1/2 * playerHeight,1/5 * playerWidth);
                    this->setRotation(0);
                    lastOrientation.clear();
                    lastOrientation.append(false);
                    lastOrientation.append(false);
                    lastOrientation.append(false);
                    lastOrientation.append(true);

                    newPos = false;
                }
                else
                {
                    setPos(x()+playerSpeed,y());
                    newPos = true;
                }
            }
            else
            {
                endCondition();
            }
        }
    }
    else
    {
        if (lastKey == Qt::Key_W)
        {
            if (pos().y() > 0)
            {
                setPos(x(),y() - playerSpeed);
            }
            else
            {
                endCondition();
            }
        }
        else if (lastKey == Qt::Key_S)
        {
            if (pos().y() + playerHeight < canvasHeight)
            {
                setPos(x(),y() + playerSpeed);
            }
            else
            {
                endCondition();
            }
        }
        else if (lastKey == Qt::Key_A)
        {
            if (pos().x() > 0)
            {
                setPos(x() - playerSpeed,y());
            }
            else
            {
                endCondition();
            }
        }
        else if (lastKey == Qt::Key_D)
        {
            if (pos().x() + playerHeight < canvasWidth)
            {
                setPos(x() + playerSpeed,y());
            }
            else
            {
                endCondition();
            }
        }
    }
}

void Player::trail()
{
    // On ajoute une trainée seulement si l'avatar s'est déplacé à cette itération
    if(newPos)
    {
        if (lastOrientation[0] == true)
        {
            // L'avatar se déplace vers le haut
            QGraphicsRectItem *rectangle = new QGraphicsRectItem(lastPosx,lastPosy + playerHeight + 1, playerWidth, playerSpeed);
            game->scene->addItem(rectangle);

            /*
            A FAIRE :
            changer l'image de la moto en coloriant l'outline pour voir les delimitations exactes de la photo pour voir
            si les qgraphicsrectitem spawnent au bon endroit ou non.
            */
        }
        else if (lastOrientation[1] == true)
        {

        }
        else if (lastOrientation[2] == true)
        {

        }
        else
        {

        }
    }
}
