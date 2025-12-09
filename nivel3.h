#ifndef NIVEL3_H
#define NIVEL3_H

#include "Nivel.h"
#include "Soldado.h"
#include "EnemigoSoldadoIA.h"
#include "proyectiln3.h"
#include "entidad.h"

#include <QVector>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QKeyEvent>

class Nivel3 : public Nivel
{
    Q_OBJECT

public:
    explicit Nivel3(QObject *parent = nullptr);

    void establecerBandoJugadorUcrania(bool esUcrania);

    void iniciarNivel() override;
    void actualizarFrame() override;
    void procesarTeclaPresionada(QKeyEvent *eventoTecla) override;
    void procesarTeclaLiberada(QKeyEvent *eventoTecla) override;

private:
    void crearEscenario();
    void crearJugador();
    void crearEnemigos();

    void crearProyectilJugador();
    void crearProyectilEnemigo(EnemigoSoldadoIA *enemigo);

    void actualizarProyectilesJugador();
    void actualizarProyectilesEnemigos();

    void verificarColisionesProyectilesConEnemigos();
    void verificarColisionesProyectilesEnemigosConJugador();

    void gestionarMuerteJugador();
    void actualizarTextoVidas();
    void actualizarTextoTiempo();
    void manejarFinPorTiempo();

    void marcarVictoria();
    void marcarDerrota();

    // UI barras de vida
    void crearUI();
    void actualizarBarraVida();
    void actualizarBarraVidaJugador();
    void actualizarBarraVidaEnemigo();

    void resolverColisionJugadorEnemigos();

    void limitarEntidadEnX_N3(Entidad *entidad, float anchoSprite);

    void mostrarFondoResultado(bool jugadorGana);

    void reiniciarRonda();

    Soldado *jugador;
    QVector<EnemigoSoldadoIA*> enemigos;
    QVector<int> tiempoDisparoEnemigos;

    QVector<ProyectilN3*> proyectilesJugador;
    QVector<ProyectilN3*> proyectilesEnemigos;

    bool jugadorEsUcrania;

    int vidasJugador;
    int vidasEnemigo;
    QGraphicsTextItem *textoVidas;

    int tiempoCombateSegundos;
    int contadorFramesTiempo;
    QGraphicsTextItem *textoTiempo;

    bool combateFinalizado;

    bool jugadorEstabaMuerto;

    QGraphicsRectItem *barraVidaJugadorFondo;
    QGraphicsRectItem *barraVidaJugadorRelleno;

    QGraphicsRectItem *barraVidaEnemigoFondo;
    QGraphicsRectItem *barraVidaEnemigoRelleno;

    QGraphicsTextItem *labelVidaJugador;
    QGraphicsTextItem *labelVidaEnemigo;

    QGraphicsPixmapItem *iconoTiempo;
    QGraphicsPixmapItem *fondoResultado;
};

#endif // NIVEL3_H
