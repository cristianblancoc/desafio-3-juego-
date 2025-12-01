#include "Nivel.h"
#include "Entidad.h"

#include <QKeyEvent>
#include <QDebug>

Nivel::Nivel(int numeroNivel, QObject *parent)
    : QGraphicsScene(parent)
    , numeroNivel(numeroNivel)
    , temporizador(new QTimer(this))
    , milisegundosPorFrame(16)
    , enCombate(true)
    , textoCuentaRegresiva(nullptr)
    , segundosRestantes(0)
    , contadorFramesCuenta(0)
    , framesPorSegundo(60)
    , textoResultado(nullptr)
    , resultadoMostrado(false)
{
    connect(temporizador, &QTimer::timeout,
            this, &Nivel::onActualizarFrame);
}

Nivel::~Nivel() {}
