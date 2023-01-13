#include "tronplayer.h"
#include "game.h"
#include <QApplication>
#include <QBrush>
#include <QDebug>

extern Game *game;

TronPlayer::TronPlayer(int playerNumber, int startX, int startY, int difficulty)
    : m_startX(startX),
      m_startY(startY),
      m_playerNumber(playerNumber),
      m_dx(0),
      m_dy(0),
      m_paused(false),
      m_scoreText(nullptr),
      m_trail(nullptr)
{
    setRect(startX, startY, 10, 10);
    setBrush(QBrush(Qt::red));

    if (difficulty == 0){
        // Difficulté facile
        m_speed = 1;
    } else if (difficulty == 1){
        // Difficulté moyenne
        m_speed = 3;
    } else {
        // Difficulté difficle
        m_speed = 5;
    }

    // Règle les orientations initiales des 2 joueurs
    if (playerNumber == 1) {
        m_dx = m_speed;
        m_dy = 0;
        m_lastOrientation = 0;
    } else {
        m_dx = -m_speed;
        m_dy = 0;
        m_lastOrientation = 1;
    }
}

TronPlayer::~TronPlayer()
{
    delete m_trail;
}

/*
 * Cette fonction gère les événements de pression de touche pour la classe TronPlayer. Elle définit la direction de
 * déplacement du joueur en fonction des touches pressées. Si la barre d'espace est pressée, elle met en pause ou
 * réactive l'état de pause du jeu.
 *
 * Le premier joueur se déplace en appuyant sur les touches WASD (W -> haut, A -> gauche, S -> bas, D -> droite).
 * Le second joueur se déplace en appuyant sur les touches des flèches.
 *
*/
void TronPlayer::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_W:
            if (m_playerNumber == 1) {
                m_dx = 0;
                m_dy = -m_speed;
                m_lastOrientation = 2;
                m_turning = true;
                m_turningCounter = true;
            }
            break;
        case Qt::Key_A:
            if (m_playerNumber == 1) {
                m_dx = -m_speed;
                m_dy = 0;
                m_lastOrientation = 1;
                m_turning = true;
                m_turningCounter = true;
            }
            break;
        case Qt::Key_S:
            if (m_playerNumber == 1) {
                m_dx = 0;
                m_dy = m_speed;
                m_lastOrientation = 3;
                m_turning = true;
                m_turningCounter = true;
            }
            break;
        case Qt::Key_D:
            if (m_playerNumber == 1) {
                m_dx = m_speed;
                m_dy = 0;
                m_lastOrientation = 0;
                m_turning = true;
                m_turningCounter = true;
            }
            break;
        case Qt::Key_Up:
            if (m_playerNumber == 2) {
                m_dx = 0;
                m_dy = -m_speed;
                m_lastOrientation = 2;
                m_turning = true;
                m_turningCounter = true;
            }
            break;
        case Qt::Key_Left:
            if (m_playerNumber == 2) {
                m_dx = -m_speed;
                m_dy = 0;
                m_lastOrientation = 1;
                m_turning = true;
                m_turningCounter = true;
            }
            break;
        case Qt::Key_Down:
            if (m_playerNumber == 2) {
                m_dx = 0;
                m_dy = m_speed;
                m_lastOrientation = 3;
                m_turning = true;
                m_turningCounter = true;
            }
            break;
        case Qt::Key_Right:
            if (m_playerNumber == 2) {
                m_dx = m_speed;
                m_dy = 0;
                m_lastOrientation = 0;
                m_turning = true;
                m_turningCounter = true;
            }
            break;
        case Qt::Key_Space:
            // Mets pause
            if (m_paused) {
                m_paused = false;
            } else {
                m_paused = true;
            }
            break;
        }
}
/*
 * La fonction advanceTronPlayer() mets à jour la position du joueur, gère la création des trainées derrière le joueur
 * après s'être déplacé. Ensuite, on vérifie si le joueur entre à collision avec des murs ou avec des trainées.
 * Finalement, on va afficher le score du joueur en fonction de la longueur de la trainée du joueur.
 * Le but de compter la longueur de la trainée du joueur ne sert ici à rien :
 * Initialement, le but était de pouvoir modifier à souhait la vitesse de son joueur afin plus facilement éviter
 * les collisions en limitant sa propre vitesse. Cependant, se faciliter la tache a nécessairement un désavantage,
 * sinon le jeu n'est pas balancé. Le fait de rabaisser sa propre vitesse engendre que lorsque l'on va moins vite,
 * le joueur aura son score qui va augmenter plus lentement, vu que le score est proportionel à la longueur de la trainée,
 * et donc naturellement à la vitesse. Cependant, je n'ai pas eu le temps d'intégrer tout ces comportements. Mais le compteur
 * de score est resté intégré.J'ai intégré un compte à rebours en haut à droite de la fenêtre - une fois que ce compte à rebours
 * atteint 0, le joueur ayant le plus grand score (et donc le joueur ayant pris le plus de risque, car ayant été le plus rapide)
 * gagne. Le but de comportement est de dynamiser le jeu si aucun des joueurs ne passe à l'offensive et pour récompenser les
 * prises de risque.
 *
*/
void TronPlayer::advanceTronPlayer()
{
    // Garde en mémoire la position actuelle avant de mettre à jour sa position
    m_lastPosX = x() + m_startX;
    m_lastPosY = y() + m_startY;

    // Mets à jour la position du joueur
    setPos(x() + m_dx, y() + m_dy);

    /*
     * Gère la création des objets trainées.
     * Il est nécessaire de prendre en compte le comportement lorsque le joueur tourne sinon des trainées vont dépasser.
     * On utilise la variable booléenne m_turning qui vérifie si c'est la première instance pour laquelle on tourne.
     * Une fois que l'objet trainée est crée, on va stocker en mémoire la variable m_turningCoords.
     * On va attendre qu'un certain côté (en fonction de vers où on tourne) atteigne une condition vis-à-vis
     * de m_turningCoords définit de manière empirique.
    */
    if (m_lastOrientation == 0){
        // Le joueur se déplace vers la droite
        if (m_turning == false){
            TronTrail *m_trail = new TronTrail(m_playerNumber, m_lastPosX-6, m_lastPosY+5, m_lastPosX+m_dx-6, m_lastPosY+5);
            game->scene.addItem(m_trail);
        } else {
            if (m_turningCounter == true){
                // Garde en mémoire la variable x du côté droit du joueur
                m_turningCoords = m_lastPosX + 10;
                m_turningCounter = false;
            }
            if (m_lastPosX+6 > m_turningCoords){
                // On continue d'ajouter des trainées
                m_turning = false;
            }
        }
    } else if (m_lastOrientation == 1){
        // Le joueur se déplace vers la gauche
        if (m_turning == false){
            TronTrail *m_trail = new TronTrail(m_playerNumber, m_lastPosX+16, m_lastPosY+5, m_lastPosX+m_dx+16, m_lastPosY+5);
            game->scene.addItem(m_trail);
        } else {
            if (m_turningCounter == true){
                // Garde en mémoire la variable x du côté gauche du joueur
                m_turningCoords = m_lastPosX;
                m_turningCounter = false;
            }
            if (m_lastPosX < m_turningCoords){
                // On continue d'ajouter des trainées
                m_turning = false;
            }
        }
    } else if (m_lastOrientation == 2){
        // Le joueur se déplace vers le haut
        if (m_turning == false){
            TronTrail *m_trail = new TronTrail(m_playerNumber, m_lastPosX+5, m_lastPosY+16, m_lastPosX+5, m_lastPosY+m_dy+16);
            game->scene.addItem(m_trail);
        } else {
            if (m_turningCounter == true){
                // Garde en mémoire la variable y du haut du joueur
                m_turningCoords = m_lastPosY;
                m_turningCounter = false;
            }
            if (m_lastPosY < m_turningCoords){
                // On continue d'ajouter des trainées
                m_turning = false;
            }
        }
    } else {
        // Le joueur se déplace vers le bas
        if (m_turning == false){
            TronTrail *m_trail = new TronTrail(m_playerNumber, m_lastPosX+5, m_lastPosY-6, m_lastPosX+5, m_lastPosY+m_dy-6);
            game->scene.addItem(m_trail);
        } else {
            if (m_turningCounter == true){
                // Garde en mémoire la variable y du bas du joueur
                m_turningCoords = m_lastPosY+10;
                m_turningCounter = false;
            }
            if (m_lastPosY+6 > m_turningCoords){
                // On continue d'ajouter des trainées
                m_turning = false;
            }
        }
    }

    // Vérifie la collision avec les trainées des autres joueurs
    QList<QGraphicsItem *> collidingItems = this->collidingItems();
    for (int i = 0; i < collidingItems.size(); ++i) {
        QGraphicsItem *item = dynamic_cast<QGraphicsItem*>(collidingItems[i]);
        if (typeid(*item) == typeid(TronTrail)) {
            // End game
            qDebug() << "Joueur" << m_playerNumber << "entre en collision avec une trainée!";
            QApplication::quit();
        }
    }
    // Vérifie la collision avec les murs
    if (x() + m_startX < 0 || x() + m_startX + rect().width() > SCREEN_WIDTH || y() + m_startY < 0 || y() + m_startY + rect().height() > SCREEN_HEIGHT) {
        /* Il faut rajouter m_startX/Y aux coordonnées car x()/y() s'initialisent à la position initiale du joueur
         * Or cette position initiale du joueur par rapport au centre du repère est situé à (m_startX,m_startY) et non (0,0)
        */
        // Fin du jeu
        qDebug() << "Joueur" << m_playerNumber << "entre en collision avec un mur!";
        QApplication::quit();
    }
    // Mets à jour le score
    if (m_scoreText) {
        game->scene.removeItem(m_scoreText);
        delete m_scoreText;
    }

    // Obtiens les trainées du joueur et compte son score en fonction de la longueur de celui-ci
    QList<TronTrail*> trails; // liste de tous les objets trainées dans la fenêtre
    QList<QGraphicsItem*> items = game->scene.items(Qt::AscendingOrder);
    for (QGraphicsItem* item : items) {
        TronTrail* trail = dynamic_cast<TronTrail*>(item);
        if (trail) {
            trails.append(trail);
        }
    }

    int score = 0;
    for (TronTrail* trail : trails) {
        // Vérifie si le numéro du joueur du bout de trainée corresponds au numéro de joueur du joueur actuel
        if (trail->playerNumber() == m_playerNumber) {
            score += trail->line().length();
        }
    }
    scorePlayer = score;
    m_scoreText = new QGraphicsTextItem(QString("Player %1 score: %2").arg(m_playerNumber).arg(score));
    m_scoreText->setPos(10, m_playerNumber == 1 ? 10 : 30);
    game->scene.addItem(m_scoreText);
}
