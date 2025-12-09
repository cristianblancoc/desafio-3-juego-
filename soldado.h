#ifndef SOLDADO_H
#define SOLDADO_H

#include "personajejugador.h"
#include <QString>

class Soldado : public PersonajeJugador
{
    Q_OBJECT

public:
    explicit Soldado(QGraphicsItem *parent = nullptr);

    void empezarDisparo();
    void detenerDisparo();
    bool estaDisparandoActualmente() const;

    void establecerSpritesDisparo(
        const QString &dispararDer,
        const QString &dispararIzq
        );

private:
    bool disparando;

    QPixmap spriteDisparoDerecha;
    QPixmap spriteDisparoIzquierda;
};

#endif // SOLDADO_H
