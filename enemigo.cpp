#include "enemigo.h"
#include "Hitbox.h"
#include <QDebug>

Enemigo::Enemigo(QGraphicsItem *parent)
    : Entidad(parent)
    , danoBase(10)
    , sueloY(500)
    , eliminado(false)
    , gravedad(0.5f)
{
}

void Enemigo::establecerDanoBase(float nuevoDano)
{
    danoBase = nuevoDano;
}

float Enemigo::obtenerDanoBase() const
{
    return danoBase;
}

void Enemigo::establecerSueloY(float nuevoSueloY)
{
    sueloY = nuevoSueloY;
}

void Enemigo::actualizarMovimientoBasico()
{
    if (eliminado)
        return;

    aplicarGravedad(gravedad);
    aplicarMovimiento();

    if (posicionY >= sueloY)
    {
        posicionY = sueloY;
        velocidadY = 0;
        setPos(posicionX, posicionY);

        if (hitboxAsociada)
            hitboxAsociada->actualizarPosicion(posicionX, posicionY);
    }
}

void Enemigo::atacarEntidad(Entidad *objetivo)
{
    if (!objetivo || eliminado)
        return;

    if (objetivo->estaMuerta())
        return;

    objetivo->recibirDano(danoBase);

    if (objetivo->estaMuerta())
        qDebug() << "Entidad atacada ha muerto.";
}

void Enemigo::marcarEliminado()
{
    eliminado = true;
    vida = 0;
}

bool Enemigo::estaEliminado() const
{
    return eliminado;
}
