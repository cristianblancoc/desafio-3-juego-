#include "proyectiln3.h"
#include "Hitbox.h"
#include <QPixmap>

ProyectilN3::ProyectilN3(int direccionDisparo,
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

void ProyectilN3::establecerSprite(const QString &ruta)
{
    QPixmap img(ruta);
    if (!img.isNull())
    {
        setPixmap(img.scaled(20, 10,
                             Qt::IgnoreAspectRatio,
                             Qt::SmoothTransformation));
    }
}

void ProyectilN3::actualizarProyectil()
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

bool ProyectilN3::estaActivo() const
{
    return activo;
}

float ProyectilN3::obtenerDano() const
{
    return danoImpacto;
}

void ProyectilN3::establecerDano(float nuevoDano)
{
    danoImpacto = nuevoDano;
}
