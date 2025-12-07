#include "Nivel1.h"
#include "Soldado.h"
#include "Hitbox.h"
#include "obstaculo.h"

#include <QDebug>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QFont>

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

void Nivel1::crearEscenario()
{
    setSceneRect(0, 0, 800, 600);

    QGraphicsRectItem *suelo = new QGraphicsRectItem(0, 550, 800, 50);
    suelo->setBrush(Qt::darkGreen);
    addItem(suelo);
    seccionesSuelo.append(suelo);

    const float width = 40.0f;
    const float height = 30.0f;

    obstaculos.append(new Obstaculo(300, 520, width, height));
    obstaculos.append(new Obstaculo(480, 520, width, height));
    obstaculos.append(new Obstaculo(650, 520, width, height));

    for (Obstaculo *o : obstaculos)
        addItem(o);

    zonaMeta = new QGraphicsRectItem(740, 500, 40, 50);
    zonaMeta->setBrush(Qt::blue);
    addItem(zonaMeta);

    comandanteVisual = new QGraphicsRectItem(0, 0, 40, 60);
    comandanteVisual->setBrush(jugadorEsUcrania ? Qt::yellow : Qt::red);
    comandanteVisual->setPos(40, 490);
    addItem(comandanteVisual);
}

void Nivel1::crearJugador()
{
    jugador = new Soldado();

    QPixmap spriteJugador(40, 60);
    spriteJugador.fill(jugadorEsUcrania ? Qt::yellow : Qt::red);
    jugador->setPixmap(spriteJugador);

    jugador->establecerSueloY(500);
    jugador->establecerPosicion(120, 500);
    jugador->establecerVidaMaxima(100);
    jugador->establecerVida(100);
    jugador->establecerModoMovimiento(PersonajeJugador::ModoNivel1);
    jugador->establecerVelocidadMovimiento(4.5f);
    jugador->establecerFuerzaSalto(-20);

    Hitbox *hitboxJugador = new Hitbox(jugador, 40, 60);
    jugador->asignarHitbox(hitboxJugador);

    addItem(jugador);
}

void Nivel1::crearUI()
{
    textoComandante = new QGraphicsTextItem;
    textoComandante->setFont(QFont("Arial", 18, QFont::Bold));
    textoComandante->setDefaultTextColor(Qt::blue);
    textoComandante->setPos(50, 50);
    textoComandante->setPlainText(
        "Acércate al comandante para recibir instrucciones.");
    addItem(textoComandante);

    textoTiempo = new QGraphicsTextItem;
    textoTiempo->setFont(QFont("Arial", 16, QFont::Bold));
    textoTiempo->setDefaultTextColor(Qt::darkRed);
    textoTiempo->setPos(600, 20);
    textoTiempo->setPlainText("Tiempo: 60");
    addItem(textoTiempo);
}
