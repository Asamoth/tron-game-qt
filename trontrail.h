#ifndef TRONTRAIL_H
#define TRONTRAIL_H

#include <QGraphicsLineItem>

class TronTrail : public QGraphicsLineItem
{
public:
    TronTrail(int playerNumber, qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = nullptr);
    int playerNumber() const;

private:
    int m_playerNumber;
};

#endif // TRONTRAIL_H
