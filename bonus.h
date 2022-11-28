#ifndef BONUS_H
#define BONUS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Bonus : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bonus(int,int,QGraphicsItem * parent=0);
private:
    QMediaPlayer * p_healthBonus;
    QMediaPlayer * p_chargeBonus;
    QMediaPlayer * p_powerUpBonus;
    int p_height;
    int p_width;
public slots:
    void Spawn();

};

#endif // BONUS_H
