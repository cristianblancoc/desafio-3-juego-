#include "spritesnivel1.h"
#include <QDebug>

spritesnivel1::spritesnivel1(QObject *parent)
    : QObject(parent), QGraphicsPixmapItem()
{
    // Carga las dos imágenes
    imgNormal = QPixmap(":/spritetanque/tanquesprite.png");
    imgAtaque = QPixmap(":/spritetanque atacando/tanquesprite.png");

    if (imgNormal.isNull())
        qDebug() << "ERROR cargando tanque_normal.png";

    if (imgAtaque.isNull())
        qDebug() << "ERROR cargando tanque_atacando.png";

    // Primera imagen visible
    setPixmap(imgNormal.scaled(anchoFinal, altoFinal,
                               Qt::KeepAspectRatio,
                               Qt::SmoothTransformation));
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
}
