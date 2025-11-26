#include "juego.h"
#include "ui_juego.h"
#include "spritesnivel1.h"
#include <QGraphicsScene>
#include <QDebug>

juego::juego(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::juego)
{
    ui->setupUi(this);

    QGraphicsScene *escena = new QGraphicsScene(this);

    int ancho = ui->graphicsView->width() - 5;
    int alto  = ui->graphicsView->height() - 5;

    int anchoFondo = ancho * 2;

    // Fondo
    QPixmap imagenFondo(":/paisaje/fondo.png");
    fondoScroll = new QGraphicsPixmapItem(
        imagenFondo.scaled(anchoFondo, alto));

    fondoScroll->setZValue(-1);
    escena->addItem(fondoScroll);

    fondoOffset = 0;

    escena->setSceneRect(0, 0, ancho, alto);
    ui->graphicsView->setScene(escena);

    // JUGADOR
    spritesnivel1 *jug1 = new spritesnivel1(ui->graphicsView);
    escena->addItem(jug1);
    jug1->setPos(200, 200);
    jug1->setFocus();

    // Señales
    connect(jug1, &spritesnivel1::llegarBorde, this, &juego::nuevaEscena);
    connect(jug1, &spritesnivel1::movDer, this, &juego::moverEscena);
    QTimer::singleShot(0, this, [=](){
        int ancho = ui->graphicsView->width();
        int alto  = ui->graphicsView->height();

        QPixmap imagenFondo(":/paisaje/fondo.png");
        QPixmap fondoEscalado = imagenFondo.scaled(
            ancho,
            alto,
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation
            );

        fondoScroll->setPixmap(fondoEscalado);
    });
}

juego::~juego()
{
    delete ui;
}

void juego::nuevaEscena()
{
    // Cambiar fondo al tocar borde
    fondoOffset = 0;
}

void juego::moverEscena()
{
    fondoOffset += 1;

    if (fondoOffset >= ancho)
        fondoOffset = 0;

    fondoScroll->setPos(-fondoOffset, 0);
}




void juego::on_pushButton_clicked()
{

}
