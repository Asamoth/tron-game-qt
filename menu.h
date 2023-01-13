#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QPushButton>

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    //~Menu();
public slots:
    void startGame();
    void showSettingsDialog();
    void menuGame();
private:
    QPushButton *m_playButton;
    QPushButton *m_settingsButton;
    QPushButton *m_quitButton;
    void m_setEasyValue();
    void m_setMediumValue();
    void m_setHardValue();
    int m_difficulty;
};

#endif // MENU_H
