#include "Soldado.h"

Soldado::Soldado(QGraphicsItem *parent)
    : PersonajeJugador(parent)
    , disparando(false)
{
}

void Soldado::empezarDisparo()
{
    disparando = true;

    int dir = obtenerDireccion();

    if (dir >= 0)
    {
        if (!spriteDisparoDerecha.isNull())
            setPixmap(spriteDisparoDerecha
                          .scaled(100,100));
    }
    else
    {
        if (!spriteDisparoIzquierda.isNull())
            setPixmap(spriteDisparoIzquierda
                          .scaled(100,100));
    }
}

void Soldado::detenerDisparo()
{
    disparando = false;
}

bool Soldado::estaDisparandoActualmente() const
{
    return disparando;
}

void Soldado::establecerSpritesDisparo(
    const QString &dispararDer,
    const QString &dispararIzq
    ){
    spriteDisparoDerecha   = QPixmap(dispararDer);
    spriteDisparoIzquierda = QPixmap(dispararIzq);
}
