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

    // --- ESCENA ---
    escena = new QGraphicsScene(0, 0, ancho * 3, alto);
    ui->graphicsView->setScene(escena);

    // --- FONDO ---
    QPixmap fondo(":/paisaje/fondo3.png");

    fondo = fondo.scaled(ancho * 3, alto,
                         Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation);

    fondoScroll = new QGraphicsPixmapItem(fondo);
    fondoScroll->setZValue(-1);
    escena->addItem(fondoScroll);

    // --- TANQUE ---
    tanque = new spritesnivel1();
    tanque->setPos(0, alto - 0);
    tanque->setZValue(10);
    escena->addItem(tanque);

    // --- TECLAS ---
    setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    this->setFocus();

    ui->graphicsView->centerOn(tanque);
}

void juego::keyPressEvent(QKeyEvent *event)
{
    int speed = 10;

    if (event->key() == Qt::Key_Left)
        tanque->setX(tanque->x() - speed);

    if (event->key() == Qt::Key_Right)
        tanque->setX(tanque->x() + speed);

    if (event->key() == Qt::Key_Up)
        tanque->setY(tanque->y() - speed);

    if (event->key() == Qt::Key_Down)
        tanque->setY(tanque->y() + speed);

    // Cambiar entre imagen normal y ataque
    if (event->key() == Qt::Key_Space)
        tanque->mostrarAtaque();

    if (event->key() == Qt::Key_A)
        tanque->mostrarNormal();
}

juego::~juego()
{
    delete ui;
}
