#ifndef JUEGO_H
#define JUEGO_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

QT_BEGIN_NAMESPACE
namespace Ui { class juego; }
QT_END_NAMESPACE

class juego : public QMainWindow
{
    Q_OBJECT

public:
    juego(QWidget *parent = nullptr);
    ~juego();

public slots:
    void nuevaEscena();
    void moverEscena();
    void on_pushButton_clicked();

private:
    Ui::juego *ui;

    int alto;
    int ancho;

    QGraphicsPixmapItem *fondoScroll;
    int fondoOffset;
};

#endif // JUEGO_H


