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

private slots:
    void volverNormal();

private:
    QPixmap imgNormal;
    QPixmap imgAtaque;

    QTimer *timerAtaque;

    // Barra de vida
    QGraphicsRectItem *barraFondo;
    QGraphicsRectItem *barraVida;

    int vidaMax = 100;
    int vida = 100;
};

#endif // AVIONENEMIGO_H
