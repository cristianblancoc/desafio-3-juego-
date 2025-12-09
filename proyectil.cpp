#include "proyectil.h"
#include "avionenemigo.h"
#include "spritesnivel1.h"
#include "Explosion.h"
#include <QPainter>
#include <QGraphicsScene>

proyectil::proyectil(bool derecha, int d, QObject *parent)
    : QObject(parent), haciaDerecha(derecha), danio(d)
{
    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, &proyectil::mover);
    t->start(16);
}

QRectF proyectil::boundingRect() const
{
    return QRectF(0, 0, 25, 8);
}

void proyectil::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
{
    p->setBrush(Qt::black);
    p->drawRect(0, 0, 25, 8);
}

void proyectil::mover()
{
    int speed = 15;
    setX(x() + (haciaDerecha ? speed : -speed));

    QList<QGraphicsItem*> col = collidingItems();

    for (auto *obj : col)
    {
        if (haciaDerecha && dynamic_cast<avionenemigo*>(obj))
        {
            ((avionenemigo*)obj)->recibirDanio(danio);
            Explosion *e = new Explosion(":/esplocionbalas/balass.png", 200);
            e->setPos(x(), y());
            scene()->addItem(e);
            delete this;
            return;
        }

        if (!haciaDerecha && dynamic_cast<spritesnivel1*>(obj))
        {
            ((spritesnivel1*)obj)->recibirDanio(danio);
            Explosion *e = new Explosion(":/esplocionbalas/balass.png", 200);
            e->setPos(x(), y());
            scene()->addItem(e);
            delete this;
            return;
        }
    }

    if (x() < -200 || x() > 5000)
        delete this;
}
