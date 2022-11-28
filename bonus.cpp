#include "bonus.h"
#include "player.h"
//#include "game.h"

#include <QList>

//extern Game * game;
Bonus::Bonus(int HEIGHT, int WIDTH, QGraphicsItem * parent) : QObject(), QGraphicsPixmapItem(parent)
{
    p_height = HEIGHT;
    p_width = WIDTH;
}

void Bonus::Spawn()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Player)){
        }
    }
}
