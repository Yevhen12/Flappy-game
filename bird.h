#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Bird : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Bird(QPixmap pixmap);

    qreal rotation() const;
    void setRotation(qreal newRotation);

    qreal y() const;
    void setY(qreal newY);
    void rotateBird(const qreal &end, const int& duration, const QEasingCurve& curve);

    void shootUp();
    void fallBird();
    void startFly();
    void freeazeInPlace();
signals:
private:
    enum Position {
        Up,
        Middle,
        Down
    };
    void updatePixmap();

    Position position;
    bool direction;

    qreal m_rotation;
    qreal m_y;
    qreal groundPos;

    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;
};

#endif // BIRD_H
