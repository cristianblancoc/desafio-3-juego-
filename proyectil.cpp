#include "Proyectil.h"
#include "Hitbox.h"
#include <QPixmap>

Proyectil::Proyectil(int direccionDisparo,
                     float xInicial,
                     float yInicial,
                     float velocidad,
                     float dano,
                     QGraphicsItem *parent)
    : Entidad(parent)
    , direccion(direccionDisparo)
    , velocidadProyectil(velocidad)
    , danoImpacto(dano)
    , activo(true)
{
    QPixmap sprite(12, 4);
    sprite.fill(Qt::black);
    setPixmap(sprite);

    establecerPosicion(xInicial, yInicial);

    velocidadX = velocidadProyectil * direccion;
    velocidadY = 0;

    Hitbox *hb = new Hitbox(this, 12.0f, 4.0f);
    asignarHitbox(hb);
}

void Proyectil::actualizarProyectil()
{
    if (!activo)
        return;

    aplicarMovimiento();

    if (posicionX < 0 || posicionX > 800)
    {
        activo = false;
        setVisible(false);
    }
}

bool Proyectil::estaActivo() const
{
    return activo;
}

float Proyectil::obtenerDano() const
{
    return danoImpacto;
}

void Proyectil::establecerDano(float nuevoDano)
{
    danoImpacto = nuevoDano;
}
