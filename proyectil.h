#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

class proyectil : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    proyectil(bool derecha, int dano, QObject *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override;

private slots:
    void mover();

private:
    bool haciaDerecha;
    int danio;
};

#endif
