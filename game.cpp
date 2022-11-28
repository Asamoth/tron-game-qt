#include "game.h"

#include <QImage> // pour récupérer l'image pour le background
#include <QBrush> // pour la dessiner

//#include <QMediaPlayer> // pour le son
#include <QTimer> // pour le déplacement des joueurs


#include <QDebug>

Game::Game(int WIDTH, int HEIGHT, QWidget *parent) : QGraphicsView(parent)
{
    // on initialise la largeur et la hauteur de la scène

    // on crée d'abord la scène et l'image de fond
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,WIDTH,HEIGHT);
    setBackgroundBrush(QBrush(QImage(":/images/bg.png")));

    // on fait en sorte que la scène précédente soit celle qui s'affiche
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIDTH,HEIGHT);

    // on crée les joueurs
    player1 = new Player(1,20,10,5, WIDTH, HEIGHT);
    //player2 = new Player(2,20,10,5);

    // on initialise leur position
    player1->setPos(WIDTH /5, HEIGHT /5);
    //player2->setPos(*m_width *4/5, *m_height * 4/5);

    player1->setFlags(QGraphicsItem::ItemIsFocusable);
    //player2->setFlags(QGraphicsItem::ItemIsFocusable);

    player1->setFocus();
    //player2->setFocus();

    // on les ajoute à la scène
    scene->addItem(player1);
    //scene->addItem(player2);

    // on crée le score
    score = new Score();
    scene->addItem(score);

    // on mets une musique de fond
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/bgsound.mp3"));
    music->play();

    /*
    Afin de définir une vitesse de déplacement pour les avatars des joueurs qui doivent se déplacer de manière
    automatique, il s'agit de définir une période selon laquelle on va rappeler la fonction de déplacement des joueurs
    qui définit elle-même une distance de déplacement en pixels selon la direction choisie.
    */
    //qDebug() << "debug timer" ;
    //m_Timer = new QTimer(this);

    //connect(m_Timer,SIGNAL(timeout()),player1,SLOT(movePlayer()));
    //connect(m_Timer,SIGNAL(timeout()),this,SLOT(player2.movePlayer()));

    // on démarre le timer
    //start(50);
    //stop();
    //show();
}

void Game::settingsWindow()
{
    //à faire
}

//void Game::start(int ms)
//{
//    // Démarre le timer pour les slots connections
//    //le temps est en millisecondes
//    m_Timer->start(ms);
//}

//void Game::stop()
//{
//    // Stop le timer pour les slots connections
//    m_Timer->stop();
//}

void Game::gameWindow()
{
    // on crée d'abord la scène et l'image de fond
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,*m_width,*m_height);
    setBackgroundBrush(QBrush(QImage(":/images/bg.png")));

    // on fait en sorte que la scène précédente soit celle qui s'affiche
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(*m_width,*m_height);

    // on crée les joueurs
    player1 = new Player(1,20,10,5,*m_width,*m_height);
    //player2 = new Player(2,20,10,5);
    // on initialise leur position
    player1->setPos(*m_width /5, *m_height /5);
    //player2->setPos(*m_width *4/5, *m_height * 4/5);

    player1->setFlags(QGraphicsItem::ItemIsFocusable);
    //player2->setFlags(QGraphicsItem::ItemIsFocusable);

    player1->setFocus();
    //player2->setFocus();

    // on les ajoute à la scène
    scene->addItem(player1);
    //scene->addItem(player2);

    // on crée le score
    score = new Score();
    scene->addItem(score);

    // on mets une musique de fond
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/bgsound.mp3"));
    music->play();
}
