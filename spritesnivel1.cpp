#include "spritesnivel1.h"
#include <QGraphicsScene>

spritesnivel1::spritesnivel1(QObject *parent)
    : QObject(parent), QGraphicsPixmapItem()
{
    imgNormal = QPixmap(":/spritetanque/tanquesprite.png");
    imgAtaque = QPixmap(":/spritetanque atacando/tanquesprite.png");

    setPixmap(imgNormal.scaled(anchoFinal, altoFinal));

    timerAtaque = new QTimer(this);
    timerAtaque->setSingleShot(true);
    connect(timerAtaque, &QTimer::timeout, this, &spritesnivel1::mostrarNormal);
}

void spritesnivel1::mostrarNormal()
{
    setPixmap(imgNormal.scaled(anchoFinal, altoFinal));
}

void spritesnivel1::mostrarAtaque()
{
    setPixmap(imgAtaque.scaled(anchoFinal, altoFinal));
    timerAtaque->start(150);
}

void spritesnivel1::recibirDanio(int d)
{
    vida -= d;
    if (vida < 0) vida = 0;

    if (vida == 0)
    {
        Explosion *e = new Explosion(":/splocion1/esplociontanque.png", 3000);
        e->setPos(x(), y());
        scene()->addItem(e);

        hide();

        QTimer::singleShot(5000, this, [this](){
            vida = vidaMax;
            show();
        });
    }
}
