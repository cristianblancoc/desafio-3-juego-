#include "juego.h"
#include "ui_juego.h"
#include "proyectil.h"
#include "Nivel2.h"

#include <QKeyEvent>

#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QIcon>
#include <QSize>



juego::juego(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::juego)
    , vista(new QGraphicsView(this))
    , nivelActual(nullptr)
    , anchoVentana(820)
    , altoVentana(620)
    , overlaySeleccion(nullptr)
    , btnUcrania(nullptr)
    , btnRusia(nullptr)
    , lblTituloSeleccion(nullptr)
    , lblUcrania(nullptr)
    , lblRusia(nullptr)
    , jugadorEsUcrania(true)

    , btnReiniciar(nullptr)

{
    ui->setupUi(this);

    playerMusica = new QMediaPlayer(this);
    salidaAudio = new QAudioOutput(this);

    playerMusica->setAudioOutput(salidaAudio);
    salidaAudio->setVolume(0.4);  // 40% de volumen

    playerMusica->setSource(QUrl("qrc:/Sprite nivel1/Musica_juego.mp3"));
    playerMusica->setLoops(QMediaPlayer::Infinite);

    playerMusica->play();

    setWindowTitle("Juego - Sistema de Niveles");
    setFixedSize(anchoVentana, altoVentana);

    vista->setParent(ui->centralwidget);
    vista->setGeometry(0, 0, anchoVentana, altoVentana);

    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setRenderHint(QPainter::Antialiasing);
    vista->setFocusPolicy(Qt::StrongFocus);


    // Pantalla de selección de país

    btnReiniciar = new QPushButton("Reiniciar", ui->centralwidget);
    btnReiniciar->setGeometry(anchoVentana - 120, 10, 100, 30);
    btnReiniciar->setStyleSheet(
        "background-color:#c62828;"
        "color:white;"
        "font-weight:bold;"
        "border-radius:4px;"
        );
    btnReiniciar->setFocusPolicy(Qt::NoFocus);

    connect(btnReiniciar, &QPushButton::clicked, this, [this]()
            {
                reiniciarJuegoCompleto();
            });

    // Pantalla de selección de país

    crearSeleccionBando();
}

juego::~juego()
{
    delete ui;
}

void juego::establecerNivel(Nivel *nuevoNivel)
{
    if (!nuevoNivel)
        return;

    if (nivelActual)
        nivelActual->disconnect(this);

    nivelActual = nuevoNivel;

    connect(nivelActual, &Nivel::nivelGanado,
            this, &juego::manejarNivelGanado);
    connect(nivelActual, &Nivel::nivelPerdido,
            this, &juego::manejarNivelPerdido);

    vista->setScene(nivelActual);
    vista->setSceneRect(nivelActual->sceneRect());
     vista->setFocusPolicy(Qt::StrongFocus);
    vista->setFocus();
    this->setFocusPolicy(Qt::NoFocus);
}

void juego::iniciarJuego()
{
    if (nivelActual)
    {
        nivelActual->iniciarNivel();
        nivelActual->iniciarTemporizador();
    }
}

void juego::cargarNivel(int numeroNivel)
{
    if (nivelActual)
    {
        nivelActual->disconnect(this);
        nivelActual->deleteLater();
        nivelActual = nullptr;
    }

    switch (numeroNivel)
    {
    case 1:
    {
        auto *n1 = new Nivel1(this);
        n1->establecerBandoJugadorUcrania(jugadorEsUcrania);
        establecerNivel(n1);
        break;
    }
    case 2:
    {

        auto *n2 = new Nivel2(this);
        n2->setVista(vista);
        establecerNivel(n2);
        break;
    }
    case 3:
    {
        auto *n3 = new Nivel3(this);
        n3->establecerBandoJugadorUcrania(jugadorEsUcrania);
        establecerNivel(n3);
        break;
    }

    default:
        qDebug() << "Número de nivel desconocido:" << numeroNivel;
        return;
    }

    iniciarJuego();
}

void juego::manejarNivelGanado(int numeroNivel)
{
    if (numeroNivel == 1)
    {
        qDebug() << "Nivel 1 ganado → cargando Nivel 2";
        QTimer::singleShot(0, this, [this]() {
            cargarNivel(2);
        });
    }
    else if (numeroNivel == 2)
    {
        qDebug() << "Nivel 2 ganado → cargando Nivel 3";
        QTimer::singleShot(0, this, [this]() {
            cargarNivel(3);
        });
    }
    else if (numeroNivel == 3)
    {
        qDebug() << "Juego completado. ¡Ganaste todo!";
    }
}

void juego::manejarNivelPerdido(int numeroNivel)
{
    qDebug() << "Nivel" << numeroNivel << "perdido. Reiniciando.";

    QTimer::singleShot(0, this, [this, numeroNivel]() {
        cargarNivel(numeroNivel);
    });
}

void juego::crearSeleccionBando()
{
    overlaySeleccion = new QWidget(ui->centralwidget);
    overlaySeleccion->setGeometry(0, 0, anchoVentana, altoVentana);
    overlaySeleccion->setStyleSheet("background-color: white;");
    overlaySeleccion->show();

    lblTituloSeleccion = new QLabel("Elige un país", overlaySeleccion);
    lblTituloSeleccion->setAlignment(Qt::AlignCenter);
    lblTituloSeleccion->setStyleSheet("color: black; font-size: 28px; font-weight: bold;");
    lblTituloSeleccion->setFixedSize(anchoVentana, 50);
    lblTituloSeleccion->move(0, 80);

    btnUcrania = new QPushButton(overlaySeleccion);
    btnRusia   = new QPushButton(overlaySeleccion);

    btnUcrania->setIcon(QIcon(":/Sprite nivel3/Bandera_Ucrania.png"));
    btnRusia->setIcon(QIcon(":/Sprite nivel3/Bandera_Russia.png"));

    btnUcrania->setIconSize(QSize(150, 150));
    btnRusia->setIconSize(QSize(150, 150));

    btnUcrania->setFixedSize(170, 170);
    btnRusia->setFixedSize(170, 170);

    int y = 260;
    btnUcrania->move(220, y);
    btnRusia->move(440, y);

    QString estilo =
        "background:#e0e0e0;"
        "border:2px solid #aaaaaa;"
        "border-radius:4px;";

    btnUcrania->setStyleSheet(estilo);
    btnRusia->setStyleSheet(estilo);

    lblUcrania = new QLabel("Ucrania", overlaySeleccion);
    lblRusia   = new QLabel("Rusia",   overlaySeleccion);

    lblUcrania->setAlignment(Qt::AlignCenter);
    lblRusia->setAlignment(Qt::AlignCenter);

    lblUcrania->setStyleSheet("color: black; font-size: 18px; font-weight: bold;");
    lblRusia->setStyleSheet("color: black; font-size: 18px; font-weight: bold;");

    lblUcrania->setFixedSize(170, 30);
    lblRusia->setFixedSize(170, 30);

    lblUcrania->move(220, y - 40);
    lblRusia->move(440, y - 40);

    connect(btnUcrania, &QPushButton::clicked, this, [this]()
            {
                jugadorEsUcrania = true;
                overlaySeleccion->hide();
                cargarNivel(1);
            });

    connect(btnRusia, &QPushButton::clicked, this, [this]()
            {
                jugadorEsUcrania = false;
                overlaySeleccion->hide();
                cargarNivel(1);
            });

}

void juego::keyPressEvent(QKeyEvent *e)
{
    if (!nivelActual) return;

    if (auto n2 = dynamic_cast<Nivel2*>(nivelActual))
    {
        n2->moverTanqueConTecla(e);
        return;
    }
}






void juego::reiniciarJuegoCompleto()
{
    if (nivelActual)
    {
        nivelActual->disconnect(this);
        vista->setScene(nullptr);
        nivelActual->deleteLater();
        nivelActual = nullptr;
    }

    jugadorEsUcrania = true;

    if (overlaySeleccion)
    {
        overlaySeleccion->show();
        overlaySeleccion->raise();
    }

}

