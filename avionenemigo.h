#ifndef AVIONENEMIGO_H
#define AVIONENEMIGO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QPixmap>

class avionenemigo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit avionenemigo(QObject *parent = nullptr);
     void iniciarPosicionEnEscena();

    void mostrarNormal();
    void mostrarAtaque();

    void recibirDanio(int dano);
    int vida = 250;
    int vidaMax = 250;
  ;

private slots:
    void volverNormal();
    void moverVertical();
    void intentarDisparar();

private:
    QPixmap imgNormal;
    QPixmap imgAtaque;

    QTimer *timerAtaque;

    QTimer *timerMovimiento;
    QTimer *timerDisparo;

    // Barra de vida
    QGraphicsRectItem *barraFondo;
    QGraphicsRectItem *barraVida;


    // Movimiento vertical
    bool subiendo = true;
    int velocidad = 2;
    int limiteSuperior = 40;
    int limiteInferior = 600;
};

#endif // AVIONENEMIGO_H
