#include "obstaculo.h"
#include "Hitbox.h"
#include <QPixmap>

Obstaculo::Obstaculo(float x, float y, float ancho, float alto, QGraphicsItem *parent)
    : Entidad(parent)
{
    QPixmap sprite(ancho, alto);
    sprite.fill(Qt::gray);
    setPixmap(sprite);

    establecerPosicion(x, y);

    Hitbox *hb = new Hitbox(this, ancho, alto);
    asignarHitbox(hb);
}
