#ifndef PERSONAJEJUGADOR_H
#define PERSONAJEJUGADOR_H

#include "Entidad.h"

class PersonajeJugador : public Entidad
{
    Q_OBJECT

public:
    enum ModoMovimiento
    {
        ModoNivel1 = 1,
        ModoNivel2 = 2,
        ModoNivel3 = 3
    };

    explicit PersonajeJugador(QGraphicsItem *parent = nullptr);

    void establecerModoMovimiento(ModoMovimiento nuevoModo);
    ModoMovimiento obtenerModoMovimiento() const;

    void establecerSueloY(float valor);
    void establecerVelocidadMovimiento(float valor);
    void establecerFuerzaSalto(float valor);
    void establecerCooldownDisparo(int cuadros);

    void moverIzquierda();
    void moverDerecha();
    void detenerMovimientoHorizontal();
    void saltar();

    void actualizarMovimiento();

    bool puedeDisparar() const;
    void disparar();
    int  obtenerDireccion() const;

    void establecerEnSuelo(bool enSuelo);

signals:
    void proyectilDisparado(int direccion, float x, float y);

private:
    ModoMovimiento modoMovimiento;
    float velocidadMovimiento;
    float fuerzaSalto;
    float limiteSuelo;
    bool  enElAire;
    int   direccion;
    int   cooldownDisparo;
    int   contadorCooldown;

    void actualizarModoNivel1();
    void actualizarModoNivel2();
    void actualizarModoNivel3();
};

#endif // PERSONAJEJUGADOR_H
