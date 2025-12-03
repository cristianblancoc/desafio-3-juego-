#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Entidad.h"

class Enemigo : public Entidad
{
    Q_OBJECT

public:
    explicit Enemigo(QGraphicsItem *parent = nullptr);

    void establecerDanoBase(float nuevoDano);
    float obtenerDanoBase() const;

    void establecerSueloY(float nuevoSueloY);
    void actualizarMovimientoBasico();

    void atacarEntidad(Entidad *objetivo);

    void marcarEliminado();
    bool estaEliminado() const;

protected:
    float danoBase;
    float sueloY;
    bool eliminado;
    float gravedad;
};

#endif // ENEMIGO_H
