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


void EnemigoSoldadoIA::actualizarIA()
{
    if (estaEliminado() || !objetivo || objetivo->estaMuerta())
    {
        velocidadX = 0.0f;

        actualizarMovimientoBasico();
        return;
    }

    ejecutarMovimientoIA();
    actualizarMovimientoBasico();
    intentarAtacar();
}

void EnemigoSoldadoIA::ejecutarMovimientoIA()
{
    if (!objetivo)
        return;

    float dx = objetivo->obtenerPosicion().x() - obtenerPosicion().x();
    float distancia = qAbs(dx);

    if (distancia > distanciaDeteccion)
    {
        velocidadX = 0.0f;
        return;
    }

    if (dx < -1)
        velocidadX = -velocidadMovimientoIA;
    else if (dx > 1)
        velocidadX = velocidadMovimientoIA;
    else
        velocidadX = 0.0f;
}

void EnemigoSoldadoIA::intentarAtacar()
{
    if (!objetivo || estaEliminado() || objetivo->estaMuerta())
        return;

    if (contadorCuadrosAtaque > 0)
    {
        contadorCuadrosAtaque--;
        return;
    }

    Hitbox *miHitbox = obtenerHitbox();
    Hitbox *hbObjetivo = objetivo->obtenerHitbox();

    if (!miHitbox || !hbObjetivo)
        return;

    if (miHitbox->colisionaCon(hbObjetivo))
    {
        atacarEntidad(objetivo);
        contadorCuadrosAtaque = cuadrosEntreAtaques;
        qDebug() << "EnemigoSoldadoIA atacó. Vida jugador:" << objetivo->obtenerVida();
    }
}
