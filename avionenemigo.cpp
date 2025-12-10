#include "avionenemigo.h"
#include <QGraphicsScene>
#include <cstdlib>


avionenemigo::avionenemigo(QObject *parent)
    : QObject(parent), QGraphicsPixmapItem()
{
    imgNormal.load(":/avionenemigo/avionenemi.png");
    imgAtaque.load(":/spritedeavionataque/avionataque.png");

    imgNormal = imgNormal.scaledToHeight(150, Qt::SmoothTransformation);
    imgAtaque = imgAtaque.scaledToHeight(170, Qt::SmoothTransformation);

    setPixmap(imgNormal);

    timerAtaque = new QTimer(this);
    timerAtaque->setSingleShot(true);
    connect(timerAtaque, &QTimer::timeout, this, &avionenemigo::volverNormal);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &avionenemigo::moverVertical);
    timerMovimiento->start(10);

    timerDisparo = new QTimer(this);
    connect(timerDisparo, &QTimer::timeout, this, &avionenemigo::intentarDisparar);
    timerDisparo->start(500); // Cada 0.5 s intenta disparar

    barraFondo = new QGraphicsRectItem(this);
    barraVida  = new QGraphicsRectItem(barraFondo);

    barraVida->setRect(0, 0, 120, 10);
    barraVida->setBrush(QBrush(Qt::green));
}

void avionenemigo::mostrarNormal() { setPixmap(imgNormal); }
void avionenemigo::mostrarAtaque()
{
    setPixmap(imgAtaque);
    timerAtaque->start(200);
}
void avionenemigo::volverNormal() { setPixmap(imgNormal); }

void avionenemigo::activarDisparo(bool v) { puedeDisparar = v; }
void avionenemigo::iniciarPos(int x, int y) { setPos(x, y); }

void avionenemigo::moverVertical()
{
    if (subiendo) setY(y() - velocidad);
    else setY(y() + velocidad);

    if (y() <= limiteSuperior) subiendo = false;
    if (y() >= limiteInferior) subiendo = true;
}

void avionenemigo::intentarDisparar()
{
    if (!puedeDisparar) return;

    int p = rand() % 100;
    if (p < 60)
    {
        mostrarAtaque();
        proyectil *b = new proyectil(false, 50);
        b->setPos(x(), y() + pixmap().height()/2);
        if (scene())
            scene()->addItem(b);
    }
}

void avionenemigo::recibirDanio(int dano)
{
    vida -= dano;
    if (vida < 0) vida = 0;

    float pct = (float)vida / vidaMax;
    barraVida->setRect(0, 0, 120 * pct, 10);

    if (vida == 0)
    {
        Explosion *e = new Explosion(":/esplocion2/Jet Explosion in Midair.png", 1500);
        e->setPos(x(), y());
        if (scene()) scene()->addItem(e);

        puedeDisparar = false;
        setEnabled(false);
        setVisible(false);
        setPixmap(QPixmap());

        timerAtaque->stop();
        timerMovimiento->stop();
        timerDisparo->stop();

        setFlag(ItemHasNoContents, true);
        setAcceptedMouseButtons(Qt::NoButton);
    }
}

