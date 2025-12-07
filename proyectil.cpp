#include "proyectil.h"

proyectil::proyectil(bool derecha, int dano, QObject *parent)
    : QObject(parent)
{
    haciaDerecha = derecha;
    danio = dano;

    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, &proyectil::mover);
    t->start(16); // FPS
}

QRectF proyectil::boundingRect() const
{
    return QRectF(0, 0, 12, 4);
}

void proyectil::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
{
    p->setBrush(Qt::yellow);
    p->setPen(Qt::NoPen);
    p->drawRect(0, 0, 12, 4);
}

void proyectil::mover()
{
    int speed = 15;

    if (haciaDerecha)
        setX(x() + speed);
    else
        setX(x() - speed);

    if (x() > 4000 || x() < -200)
        delete this;
}
