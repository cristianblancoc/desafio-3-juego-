#ifndef SPRITESNIVEL1_H
#define SPRITESNIVEL1_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>

class spritesnivel1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit spritesnivel1(QObject *parent = nullptr);

    void mostrarNormal();
    void mostrarAtaque();

    int vida = 150;
    void recibirDanio(int d);


private:
    QPixmap imgNormal;
    QPixmap imgAtaque;

    QTimer *timerAtaque;

    int anchoFinal = 200;
    int altoFinal  = 150;
};

#endif // SPRITESNIVEL1_H
