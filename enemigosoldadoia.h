#ifndef ENEMIGOSOLDADOIA_H
#define ENEMIGOSOLDADOIA_H

#include "enemigo.h"

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

private:
    void ejecutarMovimientoIA();
    void intentarAtacar();

    Entidad *objetivo;
    float distanciaDeteccion;
    float velocidadMovimientoIA;
    int cuadrosEntreAtaques;
    int contadorCuadrosAtaque;
};

#endif // ENEMIGOSOLDADOIA_H
