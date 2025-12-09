#ifndef AVIONENEMIGO_H
#define AVIONENEMIGO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QPixmap>
#include "proyectil.h"
#include "Explosion.h"
class avionenemigo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit avionenemigo(QObject *parent = nullptr);

    //   estado
    void activarDisparo(bool v);
    void iniciarPos(int x, int y);
    bool estaVisible() const { return isVisible(); }

    void recibirDanio(int dano);

    //  Vida
    int vida = 250;
    int vidaMax = 250;
    bool puedeDisparar = false;

private slots:
    void volverNormal();
    void moverVertical();
    void intentarDisparar();

private:
    //  Imágenes
    QPixmap imgNormal;
    QPixmap imgAtaque;

    // Timers
    QTimer *timerAtaque;
    QTimer *timerMovimiento;
    QTimer *timerDisparo;

    // Barra de vida
    QGraphicsRectItem *barraFondo;
    QGraphicsRectItem *barraVida;

    // Movimiento
    bool subiendo = true;
    int velocidad = 2;
    int limiteSuperior = 40;
    int limiteInferior = 600;

    //  Mostrar estados
    void mostrarNormal();
    void mostrarAtaque();
};

#endif // AVIONENEMIGO_H
