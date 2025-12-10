#ifndef JUEGO_H
#define JUEGO_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "spritesnivel1.h"
#include "avionenemigo.h"
#include "Explosion.h"
#include <QPushButton>
#include <QGraphicsView>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>


#include "Nivel.h"
#include "Nivel1.h"
#include "Nivel2.h"

#include "Nivel3.h"
#include "ui_juego.h"

QT_BEGIN_NAMESPACE
namespace Ui { class juego; }
QT_END_NAMESPACE

class juego : public QMainWindow
{
    Q_OBJECT

public:
    explicit juego(QWidget *parent = nullptr);
    ~juego();
    void establecerNivel(Nivel *nuevoNivel);
    void iniciarJuego();
protected:
    void keyPressEvent(QKeyEvent *event) override;




private:
    Ui::juego *ui;



    QGraphicsView *vista;
    Nivel *nivelActual;

    int anchoVentana;
    int altoVentana;

    QMediaPlayer *playerMusica;
    QAudioOutput *salidaAudio;

    // Overlay de selección de país
    QWidget *overlaySeleccion;
    QPushButton *btnUcrania;
    QPushButton *btnRusia;
    QLabel *lblTituloSeleccion;
    QLabel *lblUcrania;
    QLabel *lblRusia;

    bool jugadorEsUcrania;   // true = Ucrania, false = Rusia

    QPushButton *btnReiniciar;

    void crearSeleccionBando();

    void manejarNivelGanado(int numeroNivel);
    void manejarNivelPerdido(int numeroNivel);

    Nivel* obtenerNivelActual() const;
    void cargarNivel(int numeroNivel);

    void reiniciarJuegoCompleto();

};

#endif // JUEGO_H

