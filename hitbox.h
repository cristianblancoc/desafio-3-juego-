#ifndef HITBOX_H
#define HITBOX_H

#include <QObject>
#include <QRectF>

class Entidad;

class Hitbox : public QObject
{
    Q_OBJECT

public:
    Hitbox(Entidad *entidadPropietaria, float ancho, float alto);

    void actualizarPosicion(float nuevaPosX, float nuevaPosY);
    bool colisionaCon(const Hitbox *otraHitbox) const;
    QRectF obtenerRectangulo() const;
    Entidad* obtenerEntidadPropietaria() const;

private:
    Entidad *entidadPropietaria;
    float posicionX;
    float posicionY;
    float anchoHitbox;
    float altoHitbox;
};

#endif // HITBOX_H
