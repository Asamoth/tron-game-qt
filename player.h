#ifndef PLAYER_H
#define PLAYER_H

#include <QObject> //pour les slots
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QMediaPlayer> // pour les effets sonores
#include <QList>

/*
Cette classe représente le joueur et le représente par une image. Une instance de cette classe va spawner
a un endroit du canvas en fonction du profil du joueur. Une fois le jeu lancé, ces objets vont se déplacer
dans une direction initiale définis. Le joueur va pouvoir, en intéragissant avec le clavier, changer la direction
selon laquelle le joueur va déplacer son avatar. Alors que cet avatar se déplace, celui-ci va créer une trainée
derrière lui, tout en vérifiant si cet avatar n'entre pas en collision soit avec les bords du canvas, soit avec
la trainée d'un des deux joueurs.
La partie prends fin lorsque l'un des deux joueurs entre en collision avec un objet.

*/

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT //macro pour les slots
public:
    int playerProfile;
    Player(int,int,int,int,int,int,QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    void endCondition();
private:
    QMediaPlayer * pickUpBonus;
    QTimer * Timer;
    int lastKey;
    int playerHeight;
    int playerWidth;
    int canvasHeight;
    int canvasWidth;
    int playerSpeed;
    int lastPosx;
    int lastPosy;
    bool newPos;
    QList<bool> lastOrientation ; // [Up,Down,Left,Right]
public slots:
    void movePlayer();
    void trail();
};

#endif // PLAYER_H
