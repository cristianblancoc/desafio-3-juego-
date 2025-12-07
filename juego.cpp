#include "juego.h"
#include "ui_juego.h"
#include <QKeyEvent>
#include <QDebug>

juego::juego(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::juego)
{
    ui->setupUi(this);

    int ancho = ui->graphicsView->width();
    int alto  = ui->graphicsView->height();

    //  ESCENA
    escena = new QGraphicsScene(0, 0, ancho * 3, alto);
    ui->graphicsView->setScene(escena);

    //  FONDO
    QPixmap fondo(":/paisaje/fondo3.png");
    fondo = fondo.scaled(ancho * 3, alto, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    fondoScroll = new QGraphicsPixmapItem(fondo);
    fondoScroll->setZValue(-1);
    escena->addItem(fondoScroll);

    //  TANQUE
    tanque = new spritesnivel1();
    tanque->setPos(100, alto - 150);
    tanque->setZValue(10);
    escena->addItem(tanque);
    //AVIÓN ENEMIGO
    enemigo = new avionenemigo();
    enemigo->setZValue(20);
    escena->addItem(enemigo);
    // POSICIÓN FIJA EN LA PARTE DERECHA
    enemigo->setPos( ui->graphicsView->viewport()->width() + 200, 120 );

    // TIMER PARA MOVER CÁMARA
    timerUpdate = new QTimer(this);
    connect(timerUpdate, &QTimer::timeout, this, &juego::actualizar);
    timerUpdate->start(16);

    //  FOCUS
    setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
}

void juego::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    int ancho = ui->graphicsView->width();
    int alto  = ui->graphicsView->height();

    QPixmap fondo(":/paisaje/fondo3.png");
    fondo = fondo.scaled(ancho * 3, alto, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    fondoScroll->setPixmap(fondo);
    escena->setSceneRect(0, 0, ancho * 3, alto);

    ui->graphicsView->centerOn(tanque);
    enemigo->setPos(ui->graphicsView->viewport()->width() + 200, 120);

}

void juego::actualizar()
{

    ui->graphicsView->centerOn(tanque);
}

void juego::keyPressEvent(QKeyEvent *event)
{
    int speed = 10;

    // Límites
    int maxX = escena->width()  - tanque->pixmap().width();
    int maxY = escena->height() - tanque->pixmap().height();

    int x = tanque->x();
    int y = tanque->y();

    if (event->key() == Qt::Key_Left)  x -= speed;
    if (event->key() == Qt::Key_Right) x += speed;
    if (event->key() == Qt::Key_Up)    y -= speed;
    if (event->key() == Qt::Key_Down)  y += speed;

    //  límites
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > maxX) x = maxX;
    if (y > maxY) y = maxY;

    tanque->setPos(x, y);

    // Disparo
    if (event->key() == Qt::Key_Space)
    {
        tanque->mostrarAtaque();

        proyectil *b = new proyectil(true, 50); // daño 50

        // posición delante del tanque
        b->setPos(tanque->x() + tanque->pixmap().width(), tanque->y() + tanque->pixmap().height()/2);

        escena->addItem(b);
    }

}


juego::~juego()
{
    delete ui;
}


