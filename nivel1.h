#ifndef NIVEL1_H
#define NIVEL1_H

#include "Nivel.h"
#include "Soldado.h"
#include "obstaculo.h"

#include <QVector>
#include <QStringList>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QKeyEvent>

class Nivel1 : public Nivel
{
    Q_OBJECT

public:
    explicit Nivel1(QObject *parent = nullptr);

    void iniciarNivel() override;
    void actualizarFrame() override;
    void procesarTeclaPresionada(QKeyEvent *eventoTecla) override;
    void procesarTeclaLiberada(QKeyEvent *eventoTecla) override;

    void establecerBandoJugadorUcrania(bool esUcrania);

private:
    void crearEscenario();
    void crearJugador();
    void crearUI();
    void actualizarTiempo();
    void verificarVictoria();
    void verificarCaida();
    void manejarColisionConSuelos();
    void verificarColisionObstaculo();

    // Comandante / diálogos
    void verificarInteraccionComandante();
    void iniciarDialogoComandante();
    void avanzarDialogoComandante();

    Soldado *jugador;
    QVector<QGraphicsRectItem*> seccionesSuelo;
    QGraphicsRectItem *zonaMeta;
    QGraphicsRectItem *comandanteVisual;

    QVector<Obstaculo*> obstaculos;

    QGraphicsTextItem *textoComandante;
    QGraphicsTextItem *textoTiempo;

    int tiempoRestanteFrames;

    QTimer *timerDialogoComandante;
    QStringList lineasDialogo;
    int indiceDialogo;
    bool dialogoIniciado;
    bool dialogoCompletado;

    bool jugadorEsUcrania;
};

#endif // NIVEL1_H
