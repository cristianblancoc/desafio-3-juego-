#ifndef PERSONAJEJUGADOR_H
#define PERSONAJEJUGADOR_H

#include "Entidad.h"

class PersonajeJugador : public Entidad
{
    Q_OBJECT

public:
    enum ModoMovimiento
    {
        ModoNivel1 = 1
    };

    explicit PersonajeJugador(QGraphicsItem *parent = nullptr);

    void establecerModoMovimiento(ModoMovimiento nuevoModo);
    ModoMovimiento obtenerModoMovimiento() const;

    void establecerSueloY(float valor);
    void establecerVelocidadMovimiento(float valor);
    void establecerFuerzaSalto(float valor);

    void moverIzquierda();
    void moverDerecha();
    void detenerMovimientoHorizontal();
    void saltar();

    void actualizarMovimiento();

signals:
    void proyectilDisparado(int direccion, float x, float y);

private:
    ModoMovimiento modoMovimiento;
    float velocidadMovimiento;
    float fuerzaSalto;
    float limiteSuelo;
    bool  enElAire;
    int   direccion;

    void actualizarModoNivel1();
};

#endif // PERSONAJEJUGADOR_H
