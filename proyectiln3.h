#ifndef PROYECTIL_H
#define PROYECTIL_H

#include "Entidad.h"

class Proyectil : public Entidad
{
    Q_OBJECT

public:
    explicit Proyectil(int direccionDisparo,
                       float xInicial,
                       float yInicial,
                       float velocidad,
                       float dano,
                       QGraphicsItem *parent = nullptr);

    void actualizarProyectil();
    bool estaActivo() const;
    float obtenerDano() const;
    void establecerDano(float nuevoDano);

private:
    int direccion;
    float velocidadProyectil;
    float danoImpacto;
    bool activo;
};

#endif // PROYECTIL_H
