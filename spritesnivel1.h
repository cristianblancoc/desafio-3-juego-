#ifndef SPRITESNIVEL1_H
#define SPRITESNIVEL1_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class spritesnivel1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit spritesnivel1(QObject *parent = nullptr);

    void mostrarNormal();
    void mostrarAtaque();

private:
    QPixmap imgNormal;
    QPixmap imgAtaque;

    int anchoFinal = 150;
    int altoFinal  = 100;
};

#endif // SPRITESNIVEL1_H
