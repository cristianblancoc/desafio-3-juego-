#ifndef ENEMIGOSOLDADOIA_H
#define ENEMIGOSOLDADOIA_H

#include "enemigo.h"
#include <QPixmap>
#include <QString>
class EnemigoSoldadoIA : public Enemigo
{
    Q_OBJECT

public:
    explicit EnemigoSoldadoIA(QGraphicsItem *parent = nullptr);

    void establecerObjetivo(Entidad *nuevoObjetivo);
    void establecerDistanciaDeteccion(float nuevaDistancia);
    void establecerVelocidadMovimiento(float nuevaVelocidad);
    void establecerCuadrosEntreAtaques(int cuadros);

    void actualizarIA();

    void establecerSprites(
        const QString &estatico,
        const QString &correrDer,
        const QString &correrIzq,
        const QString &saltarDer,
        const QString &saltarIzq,
        const QString &dispararDer,
        const QString &dispararIzq
        );

    void notificarDisparo(int dir);

private:
    void ejecutarMovimientoIA();
    void intentarAtacar();
    void actualizarSprite();

    Entidad *objetivo;
    float distanciaDeteccion;
    float velocidadMovimientoIA;
    int cuadrosEntreAtaques;
    int contadorCuadrosAtaque;

    QPixmap spriteEstatico;
    QPixmap spriteCorrerDerecha;
    QPixmap spriteCorrerIzquierda;
    QPixmap spriteSaltarDerecha;
    QPixmap spriteSaltarIzquierda;
    QPixmap spriteDispararDerecha;
    QPixmap spriteDispararIzquierda;

    int  direccion;
    bool disparando;
    int  contadorDisparoFrames;

    int  cuadrosQuietoAntesMover;
    int  contadorQuieto;
    bool puedeMoverse;
};

#endif // ENEMIGOSOLDADOIA_H
