#include "bird.h"
#include <QTimer>
#include <QGraphicsScene>

Bird::Bird(QPixmap pixmap) :
   position(Position::Up),
   direction(0)
{
    setPixmap(pixmap);
    QTimer * timer = new QTimer(this);

    connect(timer, &QTimer::timeout, [=]() {
        updatePixmap();
    });

    timer->start(50);

    groundPos = scenePos().y() + 430;

    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPos);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);

   //yAnimation->start();

    rotationAnimation = new QPropertyAnimation(this, "rotation", this);

    //rotateBird(90, 1000, QEasingCurve::InQuad);


}

void Bird::updatePixmap()
{
    if(position == Position::Middle){
        if(direction) {

            setPixmap(QPixmap(":/someImage/images/up.png"));
            position = Position::Up;
            direction = 0;

        } else {
            setPixmap(QPixmap(":/someImage/images/down.png"));
            position = Position::Down;
            direction = 1;
        }

    } else {
        setPixmap(QPixmap(":/someImage/images/middle.png"));
        position = Position::Middle;
    }

    setScale(0.4);


}

qreal Bird::rotation() const
{
    return m_rotation;
}

void Bird::setRotation(qreal newRotation)
{
    m_rotation = newRotation;
    QPointF c = boundingRect().center();

    QTransform transform;

    transform.translate(c.x(), c.y());
    transform.rotate(newRotation);
    transform.translate(-c.x(), -c.y());
    setTransform(transform);
}

qreal Bird::y() const
{
    return m_y;
}

void Bird::setY(qreal newY)
{
    moveBy(0, newY-m_y);
    m_y = newY;
}

void Bird::rotateBird(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);

    rotationAnimation->start();
}

void Bird::shootUp()
{
    yAnimation->stop();
    rotationAnimation->stop();

    qreal currPos = y();
    yAnimation->setStartValue(currPos);
    yAnimation->setEndValue(currPos - scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(400);

    connect(yAnimation, &QPropertyAnimation::finished, [=](){
        fallBird();
    });
    yAnimation->start();

    rotateBird(-20, 200, QEasingCurve::OutCubic);
}

void Bird::fallBird()
{
    if (y() < groundPos){
        rotationAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEndValue(groundPos);
        yAnimation->setDuration(1000);
        yAnimation->setEasingCurve(QEasingCurve::InQuad);

        yAnimation->start();

        rotateBird(90, 1000, QEasingCurve::InCubic);

    }
}

void Bird::startFly()
{
    yAnimation->start();
    rotateBird(90, 1000, QEasingCurve::InQuad);
}

void Bird::freeazeInPlace()
{
    yAnimation->stop();
    rotationAnimation->stop();
}
