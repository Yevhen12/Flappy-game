#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include <QSplashScreen>
#include <QTimer>
#include "pillar.h"
#include "scene.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new Scene(this);
    scene->setSceneRect(-250, -300, 500, 600);

    QGraphicsPixmapItem * pixIt = new QGraphicsPixmapItem(QPixmap(":/someImage/images/background.png"));
    scene->addItem(pixIt);
    pixIt->setPos(QPointF(0, 0) - QPointF(pixIt->boundingRect().width()/2, pixIt->boundingRect().height()/2));






//    Pillar * pillar = new Pillar;
//    scene->addItem(pillar);


    ui->graphicsView->setScene(scene);
    scene->addBird();


}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startGameBtn_clicked()
{
   scene->startGame();
}

