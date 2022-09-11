#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "pillar.h"
#include "bird.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addBird();

    void startGame();

    bool getGameOn() const;
    void setGameOn(bool newGameOn);
    void incrementScore();

    void setScore(int newScore);
    int boolean = 0;


signals:

private:
    void showGameOverGraphics();
    void hideGameOverGraphics();

    void pillarTimer();
    void freezeBirdAndPillars();
    void cleanPillars();

    QTimer * timer;
    Bird * bird;
    bool gameOn;

    int score;
    int bestScore;


    QGraphicsPixmapItem * gameOver;
    QGraphicsTextItem * scoreTextItem;


    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
