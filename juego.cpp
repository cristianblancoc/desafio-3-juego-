#include "juego.h"
#include "ui_juego.h"
#include "proyectil.h"

#include <QKeyEvent>

juego::juego(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::juego)
{
    ui->setupUi(this);

    int W = ui->graphicsView->width();
    int H = ui->graphicsView->height();

    escena = new QGraphicsScene(0, 0, W*3, H);
    ui->graphicsView->setScene(escena);

    // Fondo
    QPixmap f(":/paisaje/Fondo_Nivel2.png");
    f = f.scaled(W*3, H, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    fondo = new QGraphicsPixmapItem(f);
    escena->addItem(fondo);

    // Tanque
    tanque = new spritesnivel1();
    tanque->setPos(100, H - 200);
    tanque->setZValue(10);
    escena->addItem(tanque);




    // AVIÓN 1
    avion1 = new avionenemigo();
    avion1->activarDisparo(true);
    avion1->iniciarPos(1500, 200);
    escena->addItem(avion1);

    // AVIÓN 2
    avion2 = new avionenemigo();
    avion2->setVisible(false);
    avion2->activarDisparo(false);
    avion2->iniciarPos(1700, 120);
    escena->addItem(avion2);

    // AVIÓN 3
    avion3 = new avionenemigo();
    avion3->setVisible(false);
    avion3->activarDisparo(false);
    avion3->iniciarPos(1900, 250);
    escena->addItem(avion3);


    // Actualización
    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, &juego::actualizar);
    t->start(16);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    setFocus();

    QPixmap fin(":/paisaje/fonnnnn.png");
    fin = fin.scaled(1000, 700, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    finalNivel = new QGraphicsPixmapItem(fin);

    // Lo ponemos al final del campo (extremo derecho)
    finalNivel->setPos(escena->width() - 1000, H - 750);
    finalNivel->setZValue(30); // por encima del fondo

    finalNivel->setVisible(false);
    escena->addItem(finalNivel);
}

void juego::actualizar()
{
    ui->graphicsView->centerOn(tanque);
    revisarMuertes();
    if (nivelTerminado)
    {
        if (tanque->collidesWithItem(finalNivel))
        {
            qDebug() << "¡Nivel completado!";
        }
    }
}

void juego::revisarMuertes()
{
    // Si muere el avión 1
    if (avion1->vida <= 0 && !avion2->estaVisible())
    {
        avion2->setVisible(true);
        avion2->activarDisparo(true);

    }

    // Si muere el avión 2
    if (avion2->vida <= 0 && !avion3->estaVisible())
    {
        avion3->setVisible(true);
        avion3->activarDisparo(true);
    }

    if (avion3->vida <= 0 && !nivelTerminado)
    {
        nivelTerminado = true;
        finalNivel->setVisible(true);
        qDebug() << "Todos los aviones destruidos. ¡Aparece el final del nivel!";
    }

}

void juego::keyPressEvent(QKeyEvent *e)
{
    int dx = 0, dy = 0;

    if (e->key() == Qt::Key_Left)  dx = -10;
    if (e->key() == Qt::Key_Right) dx = 10;
    if (e->key() == Qt::Key_Up)    dy = -10;
    if (e->key() == Qt::Key_Down)  dy = 10;

    qreal nx = tanque->x() + dx;
    qreal ny = tanque->y() + dy;

    qreal minX = 0;
    qreal maxX = escena->width() - tanque->pixmap().width();
    qreal minY = 0;
    qreal maxY = escena->height() - tanque->pixmap().height();

    if (nx < minX) nx = minX;
    if (nx > maxX) nx = maxX;
    if (ny < minY) ny = minY;
    if (ny > maxY) ny = maxY;

    tanque->setPos(nx, ny);

    if (e->key() == Qt::Key_Space)
    {
        tanque->mostrarAtaque();

        proyectil *b = new proyectil(true, 50);
        b->setPos(tanque->x() + tanque->pixmap().width(),
                  tanque->y() + tanque->pixmap().height()/2);

        escena->addItem(b);
    }
}

juego::~juego()
{
    delete ui;
}
