#include "spritesnivel1.h"
#include <QDebug>
#include <QGraphicsScene>

spritesnivel1::spritesnivel1(QObject *parent)
    : QObject(parent), QGraphicsPixmapItem()
{
    // Cargar las dos imágenes
    imgNormal = QPixmap(":/spritetanque/tanquesprite.png");
    imgAtaque = QPixmap(":/spritetanque atacando/tanquesprite.png");

    if (imgNormal.isNull())
        qDebug() << "ERROR: no se pudo cargar tanque normal";

    if (imgAtaque.isNull())
        qDebug() << "ERROR: no se pudo cargar tanque ataque";

    // Sprite inicial
    setPixmap(imgNormal.scaled(anchoFinal, altoFinal, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // --- Timer automático para volver al estado normal ---
    timerAtaque = new QTimer(this);
    timerAtaque->setSingleShot(true);
    connect(timerAtaque, &QTimer::timeout, this, &spritesnivel1::mostrarNormal);
}

void spritesnivel1::mostrarNormal()
{
    setPixmap(imgNormal.scaled(anchoFinal, altoFinal,
                               Qt::KeepAspectRatio,
                               Qt::SmoothTransformation));
}

void spritesnivel1::mostrarAtaque()
{
    setPixmap(imgAtaque.scaled(anchoFinal, altoFinal,
                               Qt::KeepAspectRatio,
                               Qt::SmoothTransformation));

    timerAtaque->start(150); // vuelve solo
}
void spritesnivel1::recibirDanio(int d)
{
    vida -= d;
    if (vida < 0) vida = 0;

    qDebug() << "TANQUE VIDA =" << vida;

    if (vida == 0)
        hide();
}


