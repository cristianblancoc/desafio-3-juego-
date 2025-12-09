#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Explosion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Explosion(QString ruta, int duracionMs = 300, QObject *parent = nullptr)
        : QObject(parent), QGraphicsPixmapItem()
    {
        QPixmap img(ruta);
        img = img.scaledToHeight(120, Qt::SmoothTransformation);
        setPixmap(img);

        QTimer::singleShot(duracionMs, this, &Explosion::eliminar);
    }

public slots:
    void eliminar()
    {
        delete this;
    }
};

#endif // EXPLOSION_H

