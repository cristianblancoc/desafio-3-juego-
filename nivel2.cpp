#include "Nivel2.h"
#include <QDebug>

Nivel2::Nivel2(QObject *parent)
    : Nivel(2, parent)
{
    setSceneRect(0, 0, 3000, 620);

    connect(temporizador, &QTimer::timeout,
            this, &Nivel2::actualizarFrameNivel2);
}

void Nivel2::iniciarNivel()
{
    // Fondo repetido varias veces
    QPixmap imagenFondo(":/paisaje/Fondo_Nivel2.png");
    int anchoFondo = imagenFondo.width();
    int repeticiones = 5;
    for(int i = 0; i < repeticiones; i++)
    {
        QGraphicsPixmapItem* f = new QGraphicsPixmapItem(imagenFondo);
        f->setPos(i * anchoFondo, 0);
        f->setZValue(-1);
        addItem(f);
    }

    //  TANQUE
    tanque = new spritesnivel1();
    tanque->setPos(150, 500);
    addItem(tanque);

    //  AVIONES
    avion1 = new avionenemigo();
    avion1->iniciarPos(1200, 200);
    avion1->setVisible(false);
    addItem(avion1);

    avion2 = new avionenemigo();
    avion2->iniciarPos(1600, 140);
    avion2->setVisible(false);
    addItem(avion2);

    avion3 = new avionenemigo();
    avion3->iniciarPos(2000, 250);
    avion3->setVisible(false);
    addItem(avion3);

    avionActual = 1; // Primer avión activo
    activarAvion(avionActual);

    //  FINAL DEL NIVEL
    finalNivel = new QGraphicsPixmapItem(
        QPixmap(":/paisaje/fonnnnn.png").scaled(800, 500)
        );
    finalNivel->setPos(2400, 200);
    finalNivel->setZValue(20);
    finalNivel->setVisible(false);
    addItem(finalNivel);

    iniciarTemporizador();
}

void Nivel2::activarAvion(int num)
{
    switch (num)
    {
    case 1:
        avion1->setVisible(true);
        avion1->activarDisparo(true); // el timer interno maneja la probabilidad
        break;
    case 2:
        avion2->setVisible(true);
        avion2->activarDisparo(true);
        break;
    case 3:
        avion3->setVisible(true);
        avion3->activarDisparo(true);
        break;
    default: break;
    }
}

void Nivel2::actualizarFrameNivel2()
{
    if (!estaEnCombate())
        return;

    revisarMuertes();

    if (finalNivel->isVisible() &&
        tanque->collidesWithItem(finalNivel))
    {
        marcarVictoria();
    }
}

void Nivel2::actualizarFrame()
{
    actualizarFrameNivel2();
}

void Nivel2::revisarMuertes()
{
    if (!terminado)
    {
        if (avion1->vida <= 0 && avionActual == 1)
        {
            avionActual = 2;
            activarAvion(avionActual);
        }
        if (avion2->vida <= 0 && avionActual == 2)
        {
            avionActual = 3;
            activarAvion(avionActual);
        }
        if (avion3->vida <= 0 && avionActual == 3)
        {
            terminado = true;
            finalNivel->setVisible(true);
            qDebug() << "Todos los aviones destruidos → aparece final del nivel";
        }
    }
}

void Nivel2::moverTanqueConTecla(QKeyEvent *evento)
{
    if (!tanque) return;

    int dx = 0, dy = 0;
    if (evento->key() == Qt::Key_A) dx = -10;
    if (evento->key() == Qt::Key_D) dx = 10;
    if (evento->key() == Qt::Key_W) dy = -10;
    if (evento->key() == Qt::Key_S) dy = 10;

    qreal nx = tanque->x() + dx;
    qreal ny = tanque->y() + dy;

    qreal minX = 0;
    qreal minY = 0;
    qreal maxX = sceneRect().width() - tanque->pixmap().width();
    qreal maxY = sceneRect().height() - tanque->pixmap().height();

    if (nx < minX) nx = minX;
    if (nx > maxX) nx = maxX;
    if (ny < minY) ny = minY;
    if (ny > maxY) ny = maxY;

    tanque->setPos(nx, ny);

    if (vista)
        vista->centerOn(tanque);

    if (evento->key() == Qt::Key_Space)
    {
        tanque->mostrarAtaque();
        proyectil *b = new proyectil(true, 50);
        b->setPos(tanque->x() + tanque->pixmap().width(),
                  tanque->y() + tanque->pixmap().height() / 2);
        addItem(b);
    }
}

void Nivel2::procesarTeclaPresionada(QKeyEvent *evento)
{
    Q_UNUSED(evento);
}

void Nivel2::procesarTeclaLiberada(QKeyEvent *evento)
{
    Q_UNUSED(evento);
}
