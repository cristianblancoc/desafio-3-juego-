#ifndef SPRITESNIVEL1_H
#define SPRITESNIVEL1_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
#include "Explosion.h"

class spritesnivel1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit spritesnivel1(QObject *parent = nullptr);

    void mostrarNormal();
    void mostrarAtaque();
    void recibirDanio(int d);

    int vida = 150;
    int vidaMax = 300;
    void manejarTeclaPresionada(QKeyEvent *evento);
    void manejarTeclaLiberada(QKeyEvent *evento);


private:
    QPixmap imgNormal;
    QPixmap imgAtaque;
    QTimer *timerAtaque;

    int anchoFinal = 200;
    int altoFinal  = 150;
};

#endif // SPRITESNIVEL1_H
