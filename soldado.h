#ifndef SOLDADO_H
#define SOLDADO_H

#include "personajejugador.h"

class Soldado : public PersonajeJugador
{
    Q_OBJECT

public:
    explicit Soldado(QGraphicsItem *parent = nullptr);

    void empezarDisparo();
    void detenerDisparo();
    bool estaDisparandoActualmente() const;

private:
    bool disparando;
};

#endif // SOLDADO_H
