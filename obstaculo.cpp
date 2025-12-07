#include "obstaculo.h"
#include "Hitbox.h"

Obstaculo::Obstaculo(float x, float y, float ancho, float alto, QGraphicsItem *parent)
    : Entidad(parent)
{
    //setVisible(false);

    establecerPosicion(x, y);

    Hitbox *hb = new Hitbox(this, 20.0f, 20.0f);
    asignarHitbox(hb);

}
