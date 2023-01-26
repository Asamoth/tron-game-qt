#include "menu.h"
#include "game.h"
#include <QVBoxLayout>
#include <QLabel>

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
{
    menuGame();
    m_difficulty = 1; // Initially the difficulty is set to Medium
}
Game *game;
void Menu::startGame()
{
    game = new Game(60,m_difficulty);
    game->show();
}

void Menu::showSettingsDialog()
{
    // Create a new layout
    QVBoxLayout *newLayout = new QVBoxLayout;

    // Create a label for the difficulty selection
    QLabel *difficultyLabel = new QLabel("Choose the difficulty", this);
    difficultyLabel->setAlignment(Qt::AlignVCenter);

    // Create the difficulty buttons
    QPushButton *easyButton = new QPushButton("Easy", this);
    QPushButton *mediumButton = new QPushButton("Medium", this);
    QPushButton *hardButton = new QPushButton("Hard", this);
    QPushButton *returnButton = new QPushButton("Go back", this);

    // Add the widgets to the layout
    newLayout->addWidget(difficultyLabel);
    newLayout->addWidget(easyButton);
    newLayout->addWidget(mediumButton);
    newLayout->addWidget(hardButton);
    newLayout->addWidget(returnButton);

    // Set the layout as the central layout widget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(newLayout);
    /*
     It is necessary to create a central widget in order to add a layout.
     But adding a central widget adds another advantage:
     When you change configuration by clicking on a button, it
     you have to reset the window and erase everything. The act of replacing
     a central widget allows you to delete all the elements that are within it.
    */
    // Set the widget as the central widget of the main window
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

    // Create a vertical layout and add the buttons
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_playButton);
    layout->addWidget(m_settingsButton);
    layout->addWidget(m_quitButton);

    // Create a new widget and add the layout to it
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);

    // Set the widget as the central widget for the main window
    setCentralWidget(centralWidget);

    layout->setAlignment(Qt::AlignVCenter);
    layout->setSpacing(10); // Add 10 pixels of spacing between buttons

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

