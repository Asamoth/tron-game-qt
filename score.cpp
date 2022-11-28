#include "score.h"

#include <QFont> //pour modifier la police du texte affichant le score

/*
Afin d'afficher le score à différents endroits dans le canvas en fonction du profil de joueur,
on va modifier son emplacement en dehors de la classe.
*/

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    // On initialise le score à 0
    score = 0;

    // On dessine le texte qui affiche le score
    setPlainText(QString("Score: ") + QString::number(score)); //affiche "Score: 0"
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));
}

void Score::increase(){
    //on incrémente la valeur du score et on réaffiche ce nouveau score
    score++;
    setPlainText(QString("Score: ") + QString::number(score)); //Ex : affiche "Score: 1"
}

int Score::getScore(){
    return score;
}
