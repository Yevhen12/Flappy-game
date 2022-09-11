#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent},
      gameOn(false),
      score(0),
      bestScore(0)
{
    pillarTimer();



}

void Scene::addBird()
{
    bird = new Bird(QPixmap(":/someImage/images/up.png"));
    addItem(bird);
}


void Scene::pillarTimer()
{
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, [=]() {


        Pillar * pilar = new Pillar();

        connect(pilar, &Pillar::collideFail, [=]() {
            timer->stop();
            freezeBirdAndPillars();
            setGameOn(false);
            showGameOverGraphics();
            setScore(0);
        });

        addItem(pilar);
    });

    //    timer->start(1000);
}

void Scene::freezeBirdAndPillars()
{
    bird->freeazeInPlace();

    QList<QGraphicsItem *> sceenItems = items();

    foreach (QGraphicsItem * item, sceenItems) {
        Pillar * pillar = dynamic_cast<Pillar *>(item);
        if(pillar) {
            pillar->freezeInPlace();
        }
    }
}

void Scene::cleanPillars()
{
    QList<QGraphicsItem *> sceenItems = items();

    foreach (QGraphicsItem * item, sceenItems) {
        Pillar * pillar = dynamic_cast<Pillar *>(item);
        if(pillar) {
           removeItem(pillar);
           delete pillar;
        }
    }
}

void Scene::setScore(int newScore)
{
    score = newScore;
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool newGameOn)
{
    gameOn = newGameOn;
}

void Scene::incrementScore()
{
    score++;
    if(score > bestScore){
        bestScore = score;
    }
}

void Scene::showGameOverGraphics()
{
    boolean = 1;
    gameOver = new QGraphicsPixmapItem(QPixmap(":/someImage/images/game-over.png"));
    addItem(gameOver);
    gameOver->setPos(QPointF(0, 0) - QPointF(gameOver->boundingRect().width()/2, gameOver->boundingRect().height()/2));


    scoreTextItem = new QGraphicsTextItem();

    QString htmlScore = "<p> Score: " + QString::number(score) + " </p>" +
            "<p> Best score: " + QString::number(bestScore) + "</p>";

    QFont mFont ("Consolas", 30, QFont::Bold);

    scoreTextItem->setHtml(htmlScore);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::yellow);

    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0, 0) - QPointF(scoreTextItem->boundingRect().width()/2, -gameOver->boundingRect().height()/2));

}

void Scene::hideGameOverGraphics()
{
    if(gameOver && boolean) {
      removeItem(gameOver);
      delete gameOver;
      gameOver = nullptr;
    }
    if(scoreTextItem && boolean) {
      removeItem(scoreTextItem);
      delete scoreTextItem;
      scoreTextItem = nullptr;
    }
}



void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space && gameOn){
        bird->shootUp();
    }

    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && gameOn) {
        bird->shootUp();
    }

    QGraphicsScene::mousePressEvent(event);
}

void Scene::startGame()
{
    bird->startFly();

    if(!timer->isActive()) {
        cleanPillars();
        setGameOn(true);
        hideGameOverGraphics();
        timer->start(1000);
    }


}
