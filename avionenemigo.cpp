#include "avionenemigo.h"
#include <QBrush>
#include <QGraphicsScene>

avionenemigo::avionenemigo(QObject *parent)
    : QObject(parent), QGraphicsPixmapItem()
    {
    // Cargar imágenes
    imgNormal.load(":/avionenemigo/avionenemi.png");
    imgAtaque.load(":/spritedeavionataque/avionataque.png");

    // Escalar a tamaño correcto
    imgNormal = imgNormal.scaledToHeight(150, Qt::SmoothTransformation);
    imgAtaque = imgAtaque.scaledToHeight(170, Qt::SmoothTransformation);

    setPixmap(imgNormal);

    // Timer ataque
    timerAtaque = new QTimer(this);
    timerAtaque->setSingleShot(true);
    connect(timerAtaque, &QTimer::timeout, this, &avionenemigo::volverNormal);
    // Movimiento vertical
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &avionenemigo::moverVertical);
    timerMovimiento->start(10);

    // Disparo aleatorio
    timerDisparo = new QTimer(this);
    connect(timerDisparo, &QTimer::timeout, this, &avionenemigo::intentarDisparar);
    timerDisparo->start(500);   // Cada 0.5s decide si dispara

    // Barra de vida
    barraFondo = new QGraphicsRectItem(this);
    barraVida  = new QGraphicsRectItem(barraFondo);

    barraFondo->setRect(0, -20, 120, 10);
    barraFondo->setBrush(QBrush(Qt::black));

    barraVida->setRect(0, 0, 120, 10);
    barraVida->setBrush(QBrush(Qt::green));

    barraFondo->setZValue(2);
    barraVida->setZValue(3);
}


// INICIAR POSICIÓN

void avionenemigo::iniciarPosicionEnEscena()
{
    if (!scene()) return;

    // borde derecho del rectángulo real de la escena
    int x = scene()->sceneRect().right() - pixmap().width() - 10;
    int y = 100;

    setPos(x, y);
}


// Cambiar sprite

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
void avionenemigo::moverVertical()
{
    if (!scene()) return;

    if (subiendo)
        setY(y() - velocidad);
    else
        setY(y() + velocidad);

    if (y() <= limiteSuperior)
        subiendo = false;

    if (y() >= limiteInferior)
        subiendo = true;
}



// DISPARO ALEATORIO

void avionenemigo::intentarDisparar()
{
    int prob = rand() % 100;

    if (prob < 10)  // 10%
    {
        mostrarAtaque();
        qDebug() << "El avión enemigo dispara!";


    }
}


// Daño
void avionenemigo::recibirDanio(int dano)
{
    vida -= dano;
    if (vida < 0) vida = 0;

    float porcentaje = (float)vida / vidaMax;
    barraVida->setRect(0, 0, 120 * porcentaje, 10);

    qDebug() << "AVION VIDA =" << vida;

    if (vida == 0)
        hide();
}
