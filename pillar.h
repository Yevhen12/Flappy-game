#ifndef PILLAR_H
#define PILLAR_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Pillar : public QObject,  public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit Pillar();

    ~Pillar();

    qreal x() const;
    void setX(qreal newX);
    void freezeInPlace();

signals:
    void collideFail();


private:

    bool collidesWithBird();

    QGraphicsPixmapItem * topPillar;
    QGraphicsPixmapItem * bottomPillar;
    QPropertyAnimation * xAnimation;
    int positionY;


    qreal m_x;
    bool pastBird;
};

#endif // PILLAR_H
