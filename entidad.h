#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>

class Hitbox;

class Entidad
    : public QObject
    , public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Entidad(QGraphicsItem *parent = nullptr);

    void establecerPosicion(float nuevaPosX, float nuevaPosY);
    QPointF obtenerPosicion() const;

    void establecerVelocidad(float nuevaVelocidadX, float nuevaVelocidadY);
    float obtenerVelocidadX() const;
    float obtenerVelocidadY() const;

    void establecerVida(float nuevaVida);
    float obtenerVida() const;

    void establecerVidaMaxima(float nuevaVidaMaxima);
    float obtenerVidaMaxima() const;

    void aplicarMovimiento();
    void aplicarGravedad(float valorGravedad);

    void asignarHitbox(Hitbox *nuevaHitbox);
    Hitbox* obtenerHitbox() const;

    void recibirDano(float cantidadDano);
    bool estaMuerta() const;

protected:
    float posicionX;
    float posicionY;

    float velocidadX;
    float velocidadY;

    float vida;
    float vidaMaxima;

    Hitbox *hitboxAsociada;
};

#endif // ENTIDAD_H
