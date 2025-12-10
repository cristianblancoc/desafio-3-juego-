#ifndef NIVEL2_H
#define NIVEL2_H

#include "Nivel.h"
#include "spritesnivel1.h"
#include "avionenemigo.h"


#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsView>

class Nivel2 : public Nivel
{
    Q_OBJECT

public:
    explicit Nivel2(QObject *parent = nullptr);

    void iniciarNivel() override;
    void actualizarFrame() override;

    void moverTanqueConTecla(QKeyEvent *evento);
    void procesarTeclaPresionada(QKeyEvent*) override;
    void procesarTeclaLiberada(QKeyEvent*) override;

    void setVista(QGraphicsView *v) { vista = v; }

private slots:
    void actualizarFrameNivel2();

private:
    QGraphicsPixmapItem *fondo;
    spritesnivel1 *tanque;

    avionenemigo *avion1;
    avionenemigo *avion2;
    avionenemigo *avion3;

    QGraphicsPixmapItem *finalNivel;

    bool terminado = false;
    int avionActual = 1;

    void revisarMuertes();
    void activarAvion(int num);

    QGraphicsView *vista = nullptr;
};

#endif // NIVEL2_H
