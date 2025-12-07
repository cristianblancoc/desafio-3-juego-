#include "Hitbox.h"
#include "Entidad.h"

Hitbox::Hitbox(Entidad *entidadPropietaria, float ancho, float alto)
    : QObject()
    , entidadPropietaria(entidadPropietaria)
    , anchoHitbox(ancho)
    , altoHitbox(alto)
{
}

void Hitbox::actualizarDesdeEntidad()
{
    if (!entidadPropietaria)
        return;
}

bool Hitbox::colisionaCon(const Hitbox *otra) const
{
    if (!otra)
        return false;

    QRectF r1 = this->obtenerRectangulo();
    QRectF r2 = otra->obtenerRectangulo();

    return r1.intersects(r2);
}


QRectF Hitbox::obtenerRectangulo() const
{
    if (!entidadPropietaria)
        return QRectF();

    QPointF pos = entidadPropietaria->pos();

    return QRectF(
        pos.x(),
        pos.y(),
        anchoHitbox,
        altoHitbox
        );
}

Entidad* Hitbox::obtenerEntidadPropietaria() const
{
    return entidadPropietaria;
}
