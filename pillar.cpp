#include "pillar.h"
#include <QRandomGenerator>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include "bird.h"
#include "scene.h"

Pillar::Pillar() :
    pastBird(false)
{
    topPillar = new QGraphicsPixmapItem(QPixmap(":/someImage/images/pillar.png"));
    bottomPillar = new QGraphicsPixmapItem(QPixmap(":/someImage/images/pillar.png"));
    topPillar->setRotation(180);
//    topPillar->setScale(0.7);
//    bottomPillar->setScale(0.7);

    topPillar->setPos(QPointF(0, 0) - QPointF(topPillar->boundingRect().width() * (-1)/2 , topPillar->boundingRect().height()/2.5 - 50));
     bottomPillar->setPos(QPointF(0, 0) + QPointF(-bottomPillar->boundingRect().width() / 2 , 100));

    addToGroup(topPillar);
    addToGroup(bottomPillar);

    positionY = QRandomGenerator::global()->bounded(150);
    int randomXExPos = QRandomGenerator::global()->bounded(200);

    setPos(QPointF(0, 0) + QPointF(260 + randomXExPos, positionY));

    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(260 + randomXExPos);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);

    connect(xAnimation, &QPropertyAnimation::finished, [=]() {
        scene()->removeItem(this);
        delete this;

    });

    xAnimation->start();

}

Pillar::~Pillar()
{
    delete topPillar;
    delete bottomPillar;
}

qreal Pillar::x() const
{
    return m_x;
}

void Pillar::setX(qreal newX)
{
    m_x = newX;

    if(newX < 0 && !pastBird) {
        pastBird = true;
        QGraphicsScene *mScene = scene();
        Scene * myScene = dynamic_cast<Scene *>(mScene);
        if(myScene) {
            myScene->incrementScore();
        }
    }



    if(collidesWithBird()){
        emit collideFail();
    }
    setPos(QPointF(0, 0) + QPointF(newX, positionY));
}

void Pillar::freezeInPlace()
{
    xAnimation->stop();
}

bool Pillar::collidesWithBird()
{
    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());

    foreach (QGraphicsItem * item, collidingItems) {
        Bird * bird = dynamic_cast<Bird*>(item);

        if(bird) {
            return true;
        }
    }

    return false;
}

















