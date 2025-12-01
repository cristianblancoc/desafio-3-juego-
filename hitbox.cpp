#include "Hitbox.h"
#include "Entidad.h"

Hitbox::Hitbox(Entidad *entidadPropietaria, float ancho, float alto)
    : QObject()
    , entidadPropietaria(entidadPropietaria)
    , posicionX(0)
    , posicionY(0)
    , anchoHitbox(ancho)
    , altoHitbox(alto)
{
}

void Hitbox::actualizarPosicion(float nuevaPosX, float nuevaPosY)
{
    posicionX = nuevaPosX;
    posicionY = nuevaPosY;
}

bool Hitbox::colisionaCon(const Hitbox *otraHitbox) const
{
    if (!otraHitbox)
        return false;
    return obtenerRectangulo().intersects(otraHitbox->obtenerRectangulo());
}

QRectF Hitbox::obtenerRectangulo() const
{
    return QRectF(posicionX, posicionY, anchoHitbox, altoHitbox);
}

Entidad* Hitbox::obtenerEntidadPropietaria() const
{
    return entidadPropietaria;
}
