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
    , cooldownDisparo(20)
    , contadorCooldown(0)
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

void PersonajeJugador::establecerCooldownDisparo(int cuadros)
{
    cooldownDisparo = cuadros;
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

int PersonajeJugador::obtenerDireccion() const
{
    return direccion;
}

void PersonajeJugador::actualizarMovimiento()
{
    switch (modoMovimiento)
    {
    case ModoNivel1:
        actualizarModoNivel1();
        break;
    case ModoNivel2:
        actualizarModoNivel2();
        break;
    case ModoNivel3:
        actualizarModoNivel3();
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

void PersonajeJugador::actualizarModoNivel2()
{
    //Para nivel 2

}

void PersonajeJugador::actualizarModoNivel3()
{
    if (contadorCooldown > 0)
        --contadorCooldown;

    aplicarGravedad(0.6f);
    aplicarMovimiento();

    if (posicionY >= limiteSuelo)
    {
        posicionY = limiteSuelo;
        velocidadY = 0.0f;
        enElAire = false;
        setPos(posicionX, posicionY);
        if (hitboxAsociada)
            hitboxAsociada->actualizarPosicion(posicionX, posicionY);
    }
}

bool PersonajeJugador::puedeDisparar() const
{
    if (modoMovimiento != ModoNivel3)
        return false;

    return contadorCooldown <= 0;
}

void PersonajeJugador::disparar()
{
    if (!puedeDisparar())
        return;

    contadorCooldown = cooldownDisparo;
    float origenX = posicionX + 20.0f * direccion;
    float origenY = posicionY + 20.0f;
    emit proyectilDisparado(direccion, origenX, origenY);
}

void PersonajeJugador::establecerEnSuelo(bool enSuelo)
{
    enElAire = !enSuelo;
}
