#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "Entidad.h"

class Obstaculo : public Entidad
{
    Q_OBJECT

public:
    explicit Obstaculo(float x, float y, float ancho, float alto, QGraphicsItem *parent = nullptr);
};

#endif // OBSTACULO_H
