#include <QApplication>
#include "menu.h"


Menu *menu;
/*
* This game of Tron consists of two players who move leaving behind a trail.
* Players cannot pass through other walls or any players' trails, including their own.
* The object of the game is to get the opponent out of the grid by cutting them off and leading them colliding with any trail, or the walls.
* Players can move in all four directions (up, down, left, right) using their keyboard keys.
* Both players play on the same keyboard - the first player with the WASD keys, and the second player with the arrow keys on the keyboard.
* The winning player is the one who manages to survive the longest.
* The game is designed to be played on hard difficulty - other difficulties create some minor display issues when players turn
* but no real behavior problems.
*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    menu = new Menu();
    menu->show();
    return app.exec();
}
