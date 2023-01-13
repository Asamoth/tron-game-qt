#include <QApplication>
#include "menu.h"


Menu *menu;
/*
 * Ce jeu de Tron consiste en deux joueurs qui se déplacent en laissant derrière eux une trainée.
 * Les joueurs ne peuvent pas traverser les murs ni les trainées des autres joueurs.
 * Le but du jeu est de faire sortir l'adversaire de la grille en lui coupant la route ou en le faisant entrer en collision avec sa propre trainée.
 * Les joueurs peuvent se déplacer dans les quatre directions (haut, bas, gauche, droite) en utilisant les touches de leur clavier.
 * Les deux joueurs jouent sur le même clavier - le premier joueur avec les touches WASD, et le second joueur avec les touches flêchées du clavier.
 * Le joueur qui gagne est celui qui parvient à survivre le plus longtemps.
 * Le jeu est crée pour être joué en difficulté difficile - les autres difficultés créent certains problèmes mineur d'affichage lorsque les joueurs tournent
 * mais aucun réel problème de comportement.
 *
 * Je n'ai pas de fichier .ui à joindre car j'ai codé manuellement mon jeu au lieu d'utiliser des templates.
*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    menu = new Menu();
    menu->show();
    return app.exec();
}
