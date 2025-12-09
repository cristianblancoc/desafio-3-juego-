#include "juego.h"
#include "ui_juego.h"

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
    , jugadorEsUcrania(true)    // por defecto
{
    ui->setupUi(this);

    setWindowTitle("Juego - Sistema de Niveles");
    setFixedSize(anchoVentana, altoVentana);

    vista->setParent(ui->centralwidget);
    vista->setGeometry(0, 0, anchoVentana, altoVentana);

    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setRenderHint(QPainter::Antialiasing);
    vista->setFocusPolicy(Qt::StrongFocus);

    // Pantalla de selección de país (overlay que tapa todo)
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
    vista->setFocus();
}

void juego::iniciarJuego()
{
    if (nivelActual)
    {
        nivelActual->iniciarNivel();
        nivelActual->iniciarTemporizador();
    }
}

Nivel* juego::obtenerNivelActual() const
{
    return nivelActual;
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

    case 3:
    {
        auto *nivel3 = new Nivel3(this);
        nivel3->establecerBandoJugadorUcrania(jugadorEsUcrania);
        establecerNivel(nivel3);
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
        qDebug() << "Nivel 1 ganado. Cargando Nivel 3 con el país elegido.";
        QTimer::singleShot(0, this, [this]() {
            cargarNivel(3);
        });
    }
    else if (numeroNivel == 3)
    {
        qDebug() << "Juego completado. ¡Ganaste todos los niveles!";
    }
}

void juego::manejarNivelPerdido(int numeroNivel)
{
    qDebug() << "Nivel" << numeroNivel << "perdido. Reiniciando nivel.";

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

    int yBotones = 260;
    btnUcrania->move(220, yBotones);
    btnRusia->move(440, yBotones);

    QString estiloBoton =
        "background:#e0e0e0;"
        "border:2px solid #aaaaaa;"
        "border-radius:4px;";

    btnUcrania->setStyleSheet(estiloBoton);
    btnRusia->setStyleSheet(estiloBoton);

    btnUcrania->setCursor(Qt::PointingHandCursor);
    btnRusia->setCursor(Qt::PointingHandCursor);

    lblUcrania = new QLabel("Ucrania", overlaySeleccion);
    lblRusia   = new QLabel("Rusia", overlaySeleccion);

    lblUcrania->setAlignment(Qt::AlignCenter);
    lblRusia->setAlignment(Qt::AlignCenter);

    lblUcrania->setStyleSheet("color: black; font-size: 18px; font-weight: bold;");
    lblRusia->setStyleSheet("color: black; font-size: 18px; font-weight: bold;");

    lblUcrania->setFixedSize(170, 30);
    lblRusia->setFixedSize(170, 30);

    lblUcrania->move(220, yBotones - 40);
    lblRusia->move(440, yBotones - 40);


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
