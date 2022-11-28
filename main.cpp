#include <QApplication>
#include "game.h"
#include <QDebug>

/*
Ce projet est un jeu ...
*/

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "avant la game" ;
    game = new Game(600,600);
    qDebug() << "avant affichage de la game" ;
    game->show();
    qDebug() << "après la game" ;

    return a.exec();
}
