#include "Soldado.h"

Soldado::Soldado(QGraphicsItem *parent)
    : PersonajeJugador(parent)
    , disparando(false)
{
}

void Soldado::empezarDisparo()
{
    disparando = true;
}

void Soldado::detenerDisparo()
{
    disparando = false;
}

bool Soldado::estaDisparandoActualmente() const
{
    return disparando;
}
