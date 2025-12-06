#include "enemigosoldadoia.h"
#include "Hitbox.h"
#include <QtMath>
#include <QDebug>

EnemigoSoldadoIA::EnemigoSoldadoIA(QGraphicsItem *parent)
    : Enemigo(parent)
    , objetivo(nullptr)
    , distanciaDeteccion(300)
    , velocidadMovimientoIA(2)
    , cuadrosEntreAtaques(30)
    , contadorCuadrosAtaque(0)
{
}

void EnemigoSoldadoIA::establecerObjetivo(Entidad *nuevoObjetivo)
{
    objetivo = nuevoObjetivo;
}

void EnemigoSoldadoIA::establecerDistanciaDeteccion(float nuevaDistancia)
{
    distanciaDeteccion = nuevaDistancia;
}

void EnemigoSoldadoIA::establecerVelocidadMovimiento(float nuevaVelocidad)
{
    velocidadMovimientoIA = nuevaVelocidad;
}

void EnemigoSoldadoIA::establecerCuadrosEntreAtaques(int cuadros)
{
    cuadrosEntreAtaques = cuadros;
}


