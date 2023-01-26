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

    // Set the size of the scene
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
        // Easy difficulty
        countdown = 30;
    } else if (difficulty == 1){
        // Medium difficulty
        countdown = 20;
    } else {
        // Hard difficulty
        countdown = 10;
    }
    m_timercountdown = new QTimer(this);
    connect(m_timercountdown, &QTimer::timeout, this, &Game::updateCountdown);
    m_timercountdown->start(1000);

    m_countdownLabel = new QLabel(this);
    m_countdownLabel->setText(QString::number(countdown));

    // Define the position of the label at the top right of the window
    m_countdownLabel->setGeometry(width() - m_countdownLabel->width(), 0, m_countdownLabel->width(), m_countdownLabel->height());
    m_countdownLabel->setFixedSize(100, 50);
}

void Game::keyPressEvent(QKeyEvent *event)
{
    // Pass the event to the appropriate player based on the key that was pressed
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_A || event->key() == Qt::Key_S || event->key() == Qt::Key_D) {
        m_player1.keyPressEvent(event);
    } else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Left || event->key() == Qt::Key_Down || event->key() == Qt::Key_Right) {
        m_player2.keyPressEvent(event);
    }
}
extern Menu *menu;
void Game::updateCountdown()
{
    countdown--; // Decrease the countdown by 1 second
    if (countdown <= 0) {
        // Countdown has reached 0, stop the timer
        m_timercountdown->stop();

        qDebug() << "The countdown has ended!";
        this->close();
        menu->close();
        if (m_player1.scorePlayer > m_player2.scorePlayer){
            qDebug() << "Player1 has the highest score!";
        } else if (m_player1.scorePlayer < m_player2.scorePlayer){
            qDebug() << "Player2 has the highest score!";
        } else {
            qDebug() << "Both players have the same score!";
        }
        qDebug() << "Player1 :" << m_player1.scorePlayer;
        qDebug() << "Player2 :" << m_player2.scorePlayer;
    } else {
        // Update the countdown display on the window
        m_countdownLabel->setText(QString::number(countdown));
    }
}

