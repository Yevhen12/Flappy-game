#include "widget.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen * splashScreen = new QSplashScreen;


    splashScreen->setPixmap(QPixmap(":/someImage/images/flappy-bird.jpg"));
    splashScreen->show();

    Widget w;
    QTimer::singleShot(2500, splashScreen, SLOT(close()));
    QTimer::singleShot(5000, &w, SLOT(show()));


    return a.exec();
}
