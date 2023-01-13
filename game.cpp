#include "game.h"
#include "menu.h"

Game::Game(int pos, int difficulty)
    : scene(this), m_player1(1, pos, pos, difficulty), m_player2(2, SCREEN_WIDTH - 10 - pos, SCREEN_HEIGHT - 10 - pos, difficulty)
{
    setScene(&scene);
    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Définit la taille de la scène
    scene.setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    scene.addItem(&m_player1);
    scene.addItem(&m_player2);

    const int FPS = 60;
    connect(&m_timer, SIGNAL(timeout()), &m_player1, SLOT(advanceTronPlayer()));
    connect(&m_timer, SIGNAL(timeout()), &m_player2, SLOT(advanceTronPlayer()));
    m_timer.start(1000 / FPS);

    QMediaPlayer * m_music = new QMediaPlayer();
    m_music->setMedia(QUrl("qrc:/musique/bgsound.mp3"));
    m_music->play();

    if (difficulty == 0){
        // Difficulté facile
        countdown = 30;
    } else if (difficulty == 1){
        // Difficulté moyenne
        countdown = 20;
    } else {
        // Difficulté difficile
        countdown = 10;
    }
    m_timercountdown = new QTimer(this);
    connect(m_timercountdown, &QTimer::timeout, this, &Game::updateCountdown);
    m_timercountdown->start(1000);

    m_countdownLabel = new QLabel(this);
    m_countdownLabel->setText(QString::number(countdown));

    // Définit la position du label en haut à droite de fenêtre
    m_countdownLabel->setGeometry(width() - m_countdownLabel->width(), 0, m_countdownLabel->width(), m_countdownLabel->height());
    m_countdownLabel->setFixedSize(100, 50);
}

void Game::keyPressEvent(QKeyEvent *event)
{
    // Transmets l'événement au joueur approprié en fonction de la touche qui a été pressée
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_A || event->key() == Qt::Key_S || event->key() == Qt::Key_D) {
        m_player1.keyPressEvent(event);
    } else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Left || event->key() == Qt::Key_Down || event->key() == Qt::Key_Right) {
        m_player2.keyPressEvent(event);
    }
}
extern Menu *menu;
void Game::updateCountdown()
{
    countdown--; // Diminue le compte à rebours de 1 seconde
    if (countdown <= 0) {
        // Le compte à rebours a atteint 0, arrête le minuteur
        m_timercountdown->stop();

        qDebug() << "Le compte à rebours a terminé!";
        this->close();
        menu->close();
        if (m_player1.scorePlayer > m_player2.scorePlayer){
            qDebug() << "Player1 a le meilleur score!";
        } else if (m_player1.scorePlayer < m_player2.scorePlayer){
            qDebug() << "Player2 a le meilleur score!";
        } else {
            qDebug() << "Les deux joueurs ont le même score!";
        }
        qDebug() << "Player1 :" << m_player1.scorePlayer;
        qDebug() << "Player2 :" << m_player2.scorePlayer;
    } else {
        // Mets à jour l'affichage du compte à rebours sur la fenêtre
        m_countdownLabel->setText(QString::number(countdown));
    }
}

