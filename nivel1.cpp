#include "Nivel1.h"
#include <QDebug>
#include <QTimer>

Nivel1::Nivel1(QObject *parent)
    : Nivel(1, parent)
    , jugador(nullptr)
    , zonaMeta(nullptr)
    , comandanteVisual(nullptr)
    , textoComandante(nullptr)
    , textoTiempo(nullptr)
    , tiempoRestanteFrames(0)
    , timerDialogoComandante(nullptr)
    , indiceDialogo(0)
    , dialogoIniciado(false)
    , dialogoCompletado(false)
    , jugadorEsUcrania(true)
{
    timerDialogoComandante = new QTimer(this);
    connect(timerDialogoComandante, &QTimer::timeout,
            this, &Nivel1::avanzarDialogoComandante);
}

void Nivel1::establecerBandoJugadorUcrania(bool esUcrania)
{
    jugadorEsUcrania = esUcrania;
}

void Nivel1::iniciarNivel()
{
    clear();

    jugador = nullptr;
    seccionesSuelo.clear();
    zonaMeta = nullptr;
    comandanteVisual = nullptr;
    obstaculos.clear();
    textoComandante = nullptr;
    textoTiempo = nullptr;

    lineasDialogo.clear();
    indiceDialogo = 0;
    dialogoIniciado = false;
    dialogoCompletado = false;

    if (timerDialogoComandante)
        timerDialogoComandante->stop();

    qDebug() << "Nivel 1 iniciado.";
}
