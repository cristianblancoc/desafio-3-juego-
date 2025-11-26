#ifndef SPRITESNIVEL1_H
#define SPRITESNIVEL1_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsView>

class spritesnivel1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    qreal x = 200;
    qreal y = 200;

    int spriteX = 0;
    int spriteY = 0;
    int spriteAncho = 60;
    int spriteAlto = 60;

    QPixmap hojaSprites;
    QPixmap sprite;

    int cont = 0;
    QSize limites;

    QTimer *timerMov;
    int dx = 0;
    int dy = 0;

    QGraphicsView *vista;

public:
    explicit spritesnivel1(QGraphicsView *vista);

    void keyPressEvent(QKeyEvent *event) override;

    void movimiento();
    void configurarSprite(int dir);

public slots:
    void movContinuo();

signals:
    void llegarBorde();
    void movDer();
};

#endif // SPRITESNIVEL1_H


