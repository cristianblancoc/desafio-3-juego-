#ifndef PROYECTILN3_H
#define PROYECTILN3_H

#include "Entidad.h"

class ProyectilN3 : public Entidad
{
    Q_OBJECT

public:
    explicit ProyectilN3(int direccionDisparo,
                       float xInicial,
                       float yInicial,
                       float velocidad,
                       float dano,
                       QGraphicsItem *parent = nullptr);

    void actualizarProyectil();
    bool estaActivo() const;
    float obtenerDano() const;
    void establecerDano(float nuevoDano);

    void establecerSprite(const QString &ruta);

private:
    int direccion;
    float velocidadProyectil;
    float danoImpacto;
    bool activo;
};

#endif // PROYECTILN3_H
