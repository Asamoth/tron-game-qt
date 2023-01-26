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
        // Easy difficulty
        m_speed = 1;
    } else if (difficulty == 1){
        // Medium difficulty
        m_speed = 3;
    } else {
        // Hard difficulty
        m_speed = 5;
    }

    // Set the initial orientations of the 2 players
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
  * This function handles key press events for the TronPlayer class. It defines the direction of
  * movement of the player according to the keys pressed. If the spacebar is pressed, it pauses or
  * re-enables the game's paused state.
  *
  * The first player moves by pressing the WASD keys (W -> up, A -> left, S -> down, D -> right).
  * The second player moves by pressing the arrow keys.
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
  * The advanceTronPlayer() function updates the position of the player, manages the creation of trails behind the player
  * after moving. Then we check if the player is colliding with walls or trails.
  * Finally, we will display the score of the player according to the length of the trail of the player.
  * The purpose of counting the length of the player's trail is useless here:
  * Initially, the goal was to be able to modify the player's speed as desired in order to more easily avoid
  * collisions by limiting its own speed. However, making the task easier necessarily has a disadvantage,
  * otherwise the game is not balanced. Lowering your own speed means that when you go slower,
  * the player will have his score which will increase more slowly, since the score is proportional to the length of the trail.
  * However, I did not have time to integrate all these behaviors. But the counter
  * of score remained integrated. I integrated a countdown timer at the top right of the window - once this countdown
  * reaches 0, the player with the highest score (and therefore the player who took the most risk, because he was the fastest)
  * won. The purpose of behavior is to energize the game if none of the players goes on the offensive and to reward the
  * risk taking.
  *
*/
void TronPlayer::advanceTronPlayer()
{
    // Remember the current position before updating its position
    m_lastPosX = x() + m_startX;
    m_lastPosY = y() + m_startY;

    // Update player position
    setPos(x() + m_dx, y() + m_dy);

    /*
      * Handles the creation of trail objects.
      * It is necessary to take into account the behavior when the player turns otherwise trails will protrude.
      * We use the boolean variable m_turning which checks if this is the first instance for which we are turning.
      * Once the trailing object is created, we will store the m_turningCoords variable in memory.
      * We will wait for a certain side (depending on where we are turning) to reach a certain condition
      * for m_turningCoords, defined empirically.
    */
    if (m_lastOrientation == 0){
        // The player moves to the right
        if (m_turning == false){
            TronTrail *m_trail = new TronTrail(m_playerNumber, m_lastPosX-6, m_lastPosY+5, m_lastPosX+m_dx-6, m_lastPosY+5);
            game->scene.addItem(m_trail);
        } else {
            if (m_turningCounter == true){
                // Keep in memory the variable x on the right side of the player
                m_turningCoords = m_lastPosX + 10;
                m_turningCounter = false;
            }
            if (m_lastPosX+6 > m_turningCoords){
                // We keep adding trails
                m_turning = false;
            }
        }
    } else if (m_lastOrientation == 1){
        // The player moves to the left
        if (m_turning == false){
            TronTrail *m_trail = new TronTrail(m_playerNumber, m_lastPosX+16, m_lastPosY+5, m_lastPosX+m_dx+16, m_lastPosY+5);
            game->scene.addItem(m_trail);
        } else {
            if (m_turningCounter == true){
                // Keep in memory the variable x on the left side of the player
                m_turningCoords = m_lastPosX;
                m_turningCounter = false;
            }
            if (m_lastPosX < m_turningCoords){
                // We keep adding trails
                m_turning = false;
            }
        }
    } else if (m_lastOrientation == 2){
        // The player moves up
        if (m_turning == false){
            TronTrail *m_trail = new TronTrail(m_playerNumber, m_lastPosX+5, m_lastPosY+16, m_lastPosX+5, m_lastPosY+m_dy+16);
            game->scene.addItem(m_trail);
        } else {
            if (m_turningCounter == true){
                // Remember the player's top y variable
                m_turningCoords = m_lastPosY;
                m_turningCounter = false;
            }
            if (m_lastPosY < m_turningCoords){
                // We keep adding trails
                m_turning = false;
            }
        }
    } else {
        // The player moves down
        if (m_turning == false){
            TronTrail *m_trail = new TronTrail(m_playerNumber, m_lastPosX+5, m_lastPosY-6, m_lastPosX+5, m_lastPosY+m_dy-6);
            game->scene.addItem(m_trail);
        } else {
            if (m_turningCounter == true){
                // Keep in memory the variable y of the bottom of the player
                m_turningCoords = m_lastPosY+10;
                m_turningCounter = false;
            }
            if (m_lastPosY+6 > m_turningCoords){
                // We keep adding trails
                m_turning = false;
            }
        }
    }

    // Check for collision with other players' trails
    QList<QGraphicsItem *> collidingItems = this->collidingItems();
    for (int i = 0; i < collidingItems.size(); ++i) {
        QGraphicsItem *item = dynamic_cast<QGraphicsItem*>(collidingItems[i]);
        if (typeid(*item) == typeid(TronTrail)) {
            // End game
            qDebug() << "Player" << m_playerNumber << "collides with a trail!";
            QApplication::quit();
        }
    }
    // Check the collision with the walls
    if (x() + m_startX < 0 || x() + m_startX + rect().width() > SCREEN_WIDTH || y() + m_startY < 0 || y() + m_startY + rect().height() > SCREEN_HEIGHT) {
        /* We must add m_startX/Y to the coordinates because x()/y() are initialized at the initial position of the player
         * But this initial position of the player with respect to the center of the reference is located at (m_startX,m_startY) and not (0,0)
        */
        // End of Game
        qDebug() << "Player" << m_playerNumber << "collides with a trail!";
        QApplication::quit();
    }
    // Update the score
    if (m_scoreText) {
        game->scene.removeItem(m_scoreText);
        delete m_scoreText;
    }

    // Get the player's trails and count their score based on the length of the trail
    QList<TronTrail*> trails; // list of all trail objects in the window
    QList<QGraphicsItem*> items = game->scene.items(Qt::AscendingOrder);
    for (QGraphicsItem* item : items) {
        TronTrail* trail = dynamic_cast<TronTrail*>(item);
        if (trail) {
            trails.append(trail);
        }
    }

    int score = 0;
    for (TronTrail* trail : trails) {
        // Check if the trail end's player number matches the current player's player number
        if (trail->playerNumber() == m_playerNumber) {
            score += trail->line().length();
        }
    }
    scorePlayer = score;
    m_scoreText = new QGraphicsTextItem(QString("Player %1 score: %2").arg(m_playerNumber).arg(score));
    m_scoreText->setPos(10, m_playerNumber == 1 ? 10 : 30);
    game->scene.addItem(m_scoreText);
}
