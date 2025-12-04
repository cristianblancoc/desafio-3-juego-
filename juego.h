#ifndef JUEGO_H
#define JUEGO_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "spritesnivel1.h"
#include "avionenemigo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class juego; }
QT_END_NAMESPACE

class juego : public QMainWindow
{
    Q_OBJECT

public:
    explicit juego(QWidget *parent = nullptr);
    ~juego();


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::juego *ui;

    QGraphicsScene *escena;
    QGraphicsPixmapItem *fondoScroll;

    spritesnivel1 *tanque;
    avionenemigo *enemigo;
    QTimer *timerUpdate;
private slots:
    void actualizar();

};

#endif // JUEGO_H

