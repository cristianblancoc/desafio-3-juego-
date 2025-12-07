#include "Entidad.h"
#include "Hitbox.h"

Entidad::Entidad(QGraphicsItem *parent)
    : QObject()
    , QGraphicsPixmapItem(parent)
{
    posicionX = 0.0f;
    posicionY = 0.0f;

    velocidadX = 0.0f;
    velocidadY = 0.0f;

    vida = 100.0f;
    vidaMaxima = 100.0f;

    hitboxAsociada = nullptr;
}

void Entidad::establecerPosicion(float nuevaPosX, float nuevaPosY)
{
    posicionX = nuevaPosX;
    posicionY = nuevaPosY;
    setPos(posicionX, posicionY);

    if (hitboxAsociada)
        hitboxAsociada->actualizarDesdeEntidad();
}

QPointF Entidad::obtenerPosicion() const
{
    return QPointF(posicionX, posicionY);
}

void Entidad::establecerVelocidad(float nuevaVelocidadX, float nuevaVelocidadY)
{
    velocidadX = nuevaVelocidadX;
    velocidadY = nuevaVelocidadY;
}

float Entidad::obtenerVelocidadX() const
{
    return velocidadX;
}

float Entidad::obtenerVelocidadY() const
{
    return velocidadY;
}

void Entidad::establecerVida(float nuevaVida)
{
    vida = nuevaVida;

    if (vida > vidaMaxima)
        vida = vidaMaxima;

    if (vida < 0)
        vida = 0;
}

float Entidad::obtenerVida() const
{
    return vida;
}

void Entidad::establecerVidaMaxima(float nuevaVidaMaxima)
{
    vidaMaxima = nuevaVidaMaxima;
    if (vida > vidaMaxima)
        vida = vidaMaxima;
}

float Entidad::obtenerVidaMaxima() const
{
    return vidaMaxima;
}

void Entidad::aplicarMovimiento()
{
    posicionX += velocidadX;
    posicionY += velocidadY;

    setPos(posicionX, posicionY);

    if (hitboxAsociada)
        hitboxAsociada->actualizarDesdeEntidad();
}

void Entidad::aplicarGravedad(float valorGravedad)
{
    velocidadY += valorGravedad;
}

void Entidad::asignarHitbox(Hitbox *nuevaHitbox)
{
    hitboxAsociada = nuevaHitbox;

    if (hitboxAsociada)
        hitboxAsociada->actualizarDesdeEntidad();
}

Hitbox* Entidad::obtenerHitbox() const
{
    return hitboxAsociada;
}

void Entidad::recibirDano(float cantidadDano)
{
    vida -= cantidadDano;

    if (vida < 0)
        vida = 0;
}

bool Entidad::estaMuerta() const
{
    return vida <= 0;
}
