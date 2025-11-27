#include "juego.h"
#include "ui_juego.h"
#include "spritesnivel1.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QResizeEvent>

juego::juego(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::juego)
{
    ui->setupUi(this);

    // Crear escena
    escena = new QGraphicsScene(this);
    ui->graphicsView->setScene(escena);

    // Tamaño inicial del graphicsView
    ancho = ui->graphicsView->width();
    alto  = ui->graphicsView->height();

    if (ancho < 100) ancho = 800;
    if (alto < 100) alto = 600;

    int anchoFondo = ancho * 3;

    // === FONDO ===
    QPixmap imagen(":/paisaje/fondo3.png");
    QPixmap fondoEscalado = imagen.scaled(
        anchoFondo,
        alto,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        );

    fondoScroll = new QGraphicsPixmapItem(fondoEscalado);
    fondoScroll->setZValue(-1);
    escena->addItem(fondoScroll);

    // Tamaño exacto de la escena
    escena->setSceneRect(0, 0, ancho, alto);

    // Mostrar fondo ajustado en el view
    ui->graphicsView->fitInView(escena->sceneRect(), Qt::IgnoreAspectRatio);

    // === JUGADOR ===
    spritesnivel1 *jug1 = new spritesnivel1(ui->graphicsView);
    escena->addItem(jug1);
    jug1->setPos(200, 200);
    jug1->setFocus();

    connect(jug1, &spritesnivel1::llegarBorde, this, &juego::nuevaEscena);
    connect(jug1, &spritesnivel1::movDer, this, &juego::moverEscena);
}

juego::~juego()
{
    delete ui;
}

void juego::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    // Reescalamos el fondo cuando cambie el tamaño
    actualizarFondo();

    ui->graphicsView->fitInView(escena->sceneRect(), Qt::IgnoreAspectRatio);
}

void juego::actualizarFondo()
{
    // Tomar tamaño actual del graphicsView
    ancho = ui->graphicsView->width();
    alto  = ui->graphicsView->height();

    if (ancho < 100) ancho = 800;
    if (alto < 100) alto = 600;

    int anchoFondo = ancho * 3;

    // Volver a cargar y escalar el fondo
    QPixmap imagen(":/paisaje/fondo3.png");
    QPixmap fondoEscalado = imagen.scaled(
        anchoFondo,
        alto,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        );

    fondoScroll->setPixmap(fondoEscalado);

    // Ajustamos tamaño de la escena
    escena->setSceneRect(0, 0, ancho, alto);
}

void juego::nuevaEscena()
{
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
