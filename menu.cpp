#include "menu.h"
#include "game.h"
#include <QVBoxLayout>
#include <QLabel>

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
{
    menuGame();
    m_difficulty = 1; // Initialement, la difficulté est réglée sur Moyenne
}
Game *game;
void Menu::startGame()
{
    game = new Game(60,m_difficulty);
    game->show();
}

void Menu::showSettingsDialog()
{
    // Crée un nouveau layout
    QVBoxLayout *newLayout = new QVBoxLayout;

    // Crée un label poour la selection de difficulté
    QLabel *difficultyLabel = new QLabel("Choisir le niveau de difficulté", this);
    difficultyLabel->setAlignment(Qt::AlignVCenter);

    // Crée les boutons de difficulté
    QPushButton *easyButton = new QPushButton("Facile", this);
    QPushButton *mediumButton = new QPushButton("Moyen", this);
    QPushButton *hardButton = new QPushButton("Difficile", this);
    QPushButton *returnButton = new QPushButton("Retour", this);

    // Ajoute les widgets au layout
    newLayout->addWidget(difficultyLabel);
    newLayout->addWidget(easyButton);
    newLayout->addWidget(mediumButton);
    newLayout->addWidget(hardButton);
    newLayout->addWidget(returnButton);

    // Règle le layout en tant que le widget central du layout
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(newLayout);
    /*
    Il est nécessaire de créer un widget central afin d'ajouter un layout.
    Mais le fait d'ajouter un widget central ajoute un autre avantage :
    Lorsque l'on change de configuration en cliquant sur un bouton, il
    faut réinitialiser la fenêtre et tout effacer. Le fait de remplacer
    un widget central permet de supprimer tout les éléments qui sont en
    son sein.
    */
    // Règle le widget en tant que widget central de la fenêtre principale
    setCentralWidget(centralWidget);

    connect(easyButton, &QPushButton::clicked, this, &Menu::m_setEasyValue);
    connect(mediumButton, &QPushButton::clicked, this, &Menu::m_setMediumValue);
    connect(hardButton, &QPushButton::clicked, this, &Menu::m_setHardValue);
    connect(returnButton, &QPushButton::clicked, this, &Menu::menuGame);
}

void Menu::menuGame()
{
    setFixedSize(800, 600);

    m_playButton = new QPushButton(tr("Jouer"), this);
    m_settingsButton = new QPushButton(tr("Paramètres"), this);
    m_quitButton = new QPushButton(tr("Quitter"), this);

    m_playButton->setFixedSize(100, 50);
    m_settingsButton->setFixedSize(100, 50);
    m_quitButton->setFixedSize(100, 50);

    // Crée un layout vertical et ajouter les boutons
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_playButton);
    layout->addWidget(m_settingsButton);
    layout->addWidget(m_quitButton);

    // Crée un nouveau widget et y ajoute le layout
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);

    // Règle le widget en tant que widget central pour la fenêtre principale
    setCentralWidget(centralWidget);

    layout->setAlignment(Qt::AlignVCenter);
    layout->setSpacing(10); // Ajoute 10 pixels d'espacement entre les boutons

    connect(m_playButton, &QPushButton::clicked, this, &Menu::startGame);
    connect(m_settingsButton, &QPushButton::clicked, this, &Menu::showSettingsDialog);
    connect(m_quitButton, &QPushButton::clicked, this, &Menu::close);
}

void Menu::m_setEasyValue()
{
    m_difficulty = 0;
}

void Menu::m_setMediumValue()
{
    m_difficulty = 1;
}

void Menu::m_setHardValue()
{
    m_difficulty = 2;
}

