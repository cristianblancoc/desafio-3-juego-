#include "avionenemigo.h"
#include <QGraphicsScene>

avionenemigo::avionenemigo(QObject *parent)
    : QObject(parent), QGraphicsPixmapItem()
{
    // Cargar imágenes
    imgNormal.load(":/avionenemigo/avionenemi.png");
    imgAtaque.load(":/spritedeavionataque/avionataque.png");

    imgNormal = imgNormal.scaledToHeight(150, Qt::SmoothTransformation);
    imgAtaque = imgAtaque.scaledToHeight(170, Qt::SmoothTransformation);

    setPixmap(imgNormal);

    // Timer de ataque
    timerAtaque = new QTimer(this);
    timerAtaque->setSingleShot(true);
    connect(timerAtaque, &QTimer::timeout, this, &avionenemigo::volverNormal);

    // Movimiento vertical
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &avionenemigo::moverVertical);
    timerMovimiento->start(10);

    // Disparo
    timerDisparo = new QTimer(this);
    connect(timerDisparo, &QTimer::timeout, this, &avionenemigo::intentarDisparar);
    timerDisparo->start(500);

    // Barra de vida
    barraFondo = new QGraphicsRectItem(this);
    barraVida  = new QGraphicsRectItem(barraFondo);


    barraVida->setRect(0, 0, 120, 10);
    barraVida->setBrush(QBrush(Qt::green));
}

//  ESTADO

void avionenemigo::mostrarNormal()
{
    setPixmap(imgNormal);
}

void avionenemigo::mostrarAtaque()
{
    setPixmap(imgAtaque);
    timerAtaque->start(200);
}

void avionenemigo::volverNormal()
{
    setPixmap(imgNormal);
}

// FUNCIONES DE CONTROL

void avionenemigo::activarDisparo(bool v)
{
    puedeDisparar = v;
}

void avionenemigo::iniciarPos(int x, int y)
{
    setPos(x, y);
}

void avionenemigo::moverVertical()
{
    if (subiendo) setY(y() - velocidad);
    else          setY(y() + velocidad);

    if (y() <= limiteSuperior) subiendo = false;
    if (y() >= limiteInferior) subiendo = true;
}

//  DISPARO

void avionenemigo::intentarDisparar()
{
    if (!puedeDisparar) return;

    int p = rand() % 100;

    if (p < 60)
    {
        mostrarAtaque();

        proyectil *b = new proyectil(false, 50);
        b->setPos(x(), y() + pixmap().height()/2);

        scene()->addItem(b);
    }
}

//  VIDA
void avionenemigo::recibirDanio(int dano)
{
    vida -= dano;
    if (vida < 0) vida = 0;

    float pct = (float)vida / vidaMax;
    barraVida->setRect(0, 0, 120 * pct, 10);

    if (vida == 0)
    {
        // Explosión
        Explosion *e = new Explosion(":/esplocion2/Jet Explosion in Midair.png", 1500);
        e->setPos(x(), y());
        scene()->addItem(e);


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
