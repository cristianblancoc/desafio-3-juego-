#include "spritesnivel1.h"
#include <QKeyEvent>
#include <QDebug>

spritesnivel1::spritesnivel1(QGraphicsView *vista)
    : vista(vista)
{
    setFlag(ItemIsFocusable);

    limites = vista->scene()->sceneRect().size().toSize();

    hojaSprites.load(":/spritetanque/tanquesprite.png");
    sprite = hojaSprites.copy(0, 0, spriteAncho, spriteAlto);
    setPixmap(sprite);

    timerMov = new QTimer(this);
    connect(timerMov, &QTimer::timeout, this, &spritesnivel1::movContinuo);
}

void spritesnivel1::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_A:
        dx = -5; dy = 0;
        configurarSprite(60);
        timerMov->start(50);
        break;

    case Qt::Key_D:
        dx = 5; dy = 0;
        configurarSprite(120);
        timerMov->start(50);
        break;

    case Qt::Key_W:
        dx = 0; dy = -5;
        configurarSprite(180);
        timerMov->start(50);
        break;

    case Qt::Key_S:
        dx = 0; dy = 5;
        configurarSprite(0);
        timerMov->start(50);
        break;

    default:
        QGraphicsPixmapItem::keyPressEvent(event);
    }
}

void spritesnivel1::movimiento()
{
    x += dx;
    y += dy;

    // Borde derecha → cambiar escena
    if (x + spriteAncho > limites.width())
    {
        emit llegarBorde();
        x = 2;
    }

    // Borde izquierda
    if (x < 0)
        x = 2;

    // Borde abajo
    if (y + spriteAlto > limites.height())
        y = limites.height() - spriteAlto;

    // Borde arriba
    if (y < 0)
        y = 2;

    // Notificar movimiento a la derecha
    if (dx > 0)
        emit movDer();

    setPos(x, y);
}

void spritesnivel1::configurarSprite(int dir)
{
    spriteY = dir;
    spriteX = spriteAncho * cont;

    sprite = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(sprite);

    cont++;
    if (cont == 7)
        cont = 0;
}

void spritesnivel1::movContinuo()
{
    movimiento();
    configurarSprite(spriteY);
}
