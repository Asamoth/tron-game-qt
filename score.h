#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

/*
Cette classe a pour objectif de garder en mémoire un entier représentant le score d'un joueur.
Ensuite ce score va être afficher en haut à gauche/droite du canvas en fonction du profil du joueur.
*/


class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent=0);
    void increase();
    int getScore();
private:
    int score;
};

#endif // SCORE_H
