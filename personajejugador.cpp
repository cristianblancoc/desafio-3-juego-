#include "personajejugador.h"
#include "Hitbox.h"

PersonajeJugador::PersonajeJugador(QGraphicsItem *parent)
    : Entidad(parent)
    , modoMovimiento(ModoNivel1)
    , velocidadMovimiento(3.0f)
    , fuerzaSalto(-10.0f)
    , limiteSuelo(500.0f)
    , enElAire(false)
    , direccion(1)
{
}

void PersonajeJugador::establecerModoMovimiento(ModoMovimiento nuevoModo)
{
    modoMovimiento = nuevoModo;
}

PersonajeJugador::ModoMovimiento PersonajeJugador::obtenerModoMovimiento() const
{
    return modoMovimiento;
}

void PersonajeJugador::establecerSueloY(float valor)
{
    limiteSuelo = valor;
}

void PersonajeJugador::establecerVelocidadMovimiento(float valor)
{
    velocidadMovimiento = valor;
}

void PersonajeJugador::establecerFuerzaSalto(float valor)
{
    fuerzaSalto = valor;
}

void PersonajeJugador::moverIzquierda()
{
    velocidadX = -velocidadMovimiento;
    direccion = -1;
}

void PersonajeJugador::moverDerecha()
{
    velocidadX = velocidadMovimiento;
    direccion = 1;
}

void PersonajeJugador::detenerMovimientoHorizontal()
{
    velocidadX = 0.0f;
}

void PersonajeJugador::saltar()
{
    if (enElAire)
        return;

    velocidadY = fuerzaSalto;
    enElAire = true;
}

void PersonajeJugador::actualizarMovimiento()
{
    switch (modoMovimiento)
    {
    case ModoNivel1:
        actualizarModoNivel1();
        break;
    default:
        actualizarModoNivel1();
        break;
    }
}

void PersonajeJugador::actualizarModoNivel1()
{
    aplicarMovimiento();
}
