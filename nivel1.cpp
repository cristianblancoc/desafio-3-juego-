#include "Nivel1.h"
#include "Soldado.h"
#include "Hitbox.h"
#include "obstaculo.h"

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QFont>
#include <QDebug>
#include <QTimer>

Nivel1::Nivel1(QObject *parent)
    : Nivel(1, parent)
    , jugador(nullptr)
    , zonaMeta(nullptr)
    , comandanteVisual(nullptr)
    , textoComandante(nullptr)
    , textoTiempo(nullptr)
    , tiempoRestanteFrames(0)
    , timerDialogoComandante(nullptr)
    , indiceDialogo(0)
    , dialogoIniciado(false)
    , dialogoCompletado(false)
    , jugadorEsUcrania(true)
    , panelDialogo(nullptr)
    , iconoTiempoUI(nullptr)
{
    timerDialogoComandante = new QTimer(this);
    connect(timerDialogoComandante, &QTimer::timeout,
            this, &Nivel1::avanzarDialogoComandante);
}

void Nivel1::establecerBandoJugadorUcrania(bool esUcrania)
{
    jugadorEsUcrania = esUcrania;
}

void Nivel1::iniciarNivel()
{
    clear();

    jugador = nullptr;
    seccionesSuelo.clear();
    zonaMeta = nullptr;
    comandanteVisual = nullptr;
    obstaculos.clear();
    textoComandante = nullptr;
    textoTiempo = nullptr;
    panelDialogo = nullptr;
    iconoTiempoUI = nullptr;

    lineasDialogo.clear();
    indiceDialogo = 0;
    dialogoIniciado = false;
    dialogoCompletado = false;

    if (timerDialogoComandante)
        timerDialogoComandante->stop();

    crearEscenario();
    crearJugador();
    crearUI();

    prepararCuentaRegresiva(3);
    tiempoRestanteFrames = 60 * 60;

    qDebug() << "Nivel 1 iniciado.";
}

void Nivel1::crearEscenario()
{
    setSceneRect(0, 0, 800, 600);

    QGraphicsPixmapItem *fondo = new QGraphicsPixmapItem;

    if (jugadorEsUcrania)
        fondo->setPixmap(QPixmap(":/Sprite nivel1/Fondo nivel 1 Ukrania.png"));
    else
        fondo->setPixmap(QPixmap(":/Sprite nivel1/Fondo nivel1 Russia.png"));

    fondo->setPixmap(
        fondo->pixmap().scaled(830, 620, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
        );

    fondo->setPos(0, 0);
    fondo->setZValue(-10);
    addItem(fondo);

    QGraphicsRectItem *suelo = new QGraphicsRectItem(0, 400, 800, 50);
    suelo->setVisible(false);
    addItem(suelo);
    seccionesSuelo.append(suelo);

    const float width   = 40.0f;
    const float height  = 30.0f;

    obstaculos.append(new Obstaculo(280.0f, 360.0f, width, height));
    obstaculos.append(new Obstaculo(450.0f, 360.0f, width, height));
    obstaculos.append(new Obstaculo(620.0f, 360.0f, width, height));

    for (int i = 0; i < obstaculos.size(); ++i)
    {
        Obstaculo *o = obstaculos[i];
        addItem(o);

        QGraphicsPixmapItem *spriteMina = new QGraphicsPixmapItem(o);
        spriteMina->setPixmap(QPixmap(":/Sprite nivel1/Mina.png"));
        spriteMina->setPixmap(
            spriteMina->pixmap().scaled(60, 60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
            );

        spriteMina->setPos(0, 0);
    }


    QGraphicsPixmapItem *tanque = new QGraphicsPixmapItem;

    if (jugadorEsUcrania)
        tanque->setPixmap(QPixmap(":/Sprite nivel1/Tanque Ukrania.png"));
    else
        tanque->setPixmap(QPixmap(":/Sprite nivel1/Tanque Russia.png"));

    tanque->setPixmap(
        tanque->pixmap().scaled(120, 120, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
        );

    tanque->setPos(690, 310);
    addItem(tanque);
    zonaMeta = tanque;

    QGraphicsPixmapItem *comandante = new QGraphicsPixmapItem;

    if (jugadorEsUcrania)
        comandante->setPixmap(QPixmap(":/Sprite nivel1/Comandante Ukrania.png"));
    else
        comandante->setPixmap(QPixmap(":/Sprite nivel1/Comandante Russia.png"));

    comandante->setPixmap(
        comandante->pixmap().scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
        );

    comandante->setPos(-10, 300);
    addItem(comandante);
    comandanteVisual = comandante;
}

void Nivel1::crearJugador()
{
    jugador = new Soldado();

    if (jugadorEsUcrania)
    {
        jugador->establecerSprites(
            ":/Sprite nivel1/Soldado Ukrania Estatico.png",
            ":/Sprite nivel1/Soldado Ukrania Corriendo derecha.png",
            ":/Sprite nivel1/Soldado Ukrania Corriendo izquierda.png",
            ":/Sprite nivel1/Soldado Ukrania Saltando derecha.png",
            ":/Sprite nivel1/Soldado Ukrania Saltando izquierda.png"
            );
    }
    else
    {
        jugador->establecerSprites(
            ":/Sprite nivel1/Soldado Russia Estatico.png",
            ":/Sprite nivel1/Soldado Russia Corriendo Derecha.png",
            ":/Sprite nivel1/Soldado Russia Corriendo Izquierda.png",
            ":/Sprite nivel1/Soldado Russia Saltando Derecha.png",
            ":/Sprite nivel1/Soldado Russia Saltando Izquierda.png"
            );
    }

    jugador->establecerSueloY(310.0f);
    jugador->establecerPosicion(120.0f, 300.0f);
    jugador->establecerVidaMaxima(100.0f);
    jugador->establecerVida(100.0f);
    jugador->establecerModoMovimiento(PersonajeJugador::ModoNivel1);

    jugador->establecerVelocidadMovimiento(4.5f);
    jugador->establecerFuerzaSalto(-20.0f);

    Hitbox *hitboxJugador = new Hitbox(jugador, 40.0f, 75.0f);
    jugador->asignarHitbox(hitboxJugador);

    addItem(jugador);
}

void Nivel1::crearUI()
{
    panelDialogo = new QGraphicsPixmapItem;
    panelDialogo->setPixmap(
        QPixmap(":/Sprite nivel1/Mensaje.png")
            .scaled(600, 200, Qt::IgnoreAspectRatio, Qt::FastTransformation)
    );
    panelDialogo->setPos(10,-10);
    panelDialogo->setZValue(5);
    addItem(panelDialogo);

    textoComandante = new QGraphicsTextItem(panelDialogo);
    QFont fuente("Arial", 12, QFont::Bold);
    textoComandante->setFont(fuente);
    textoComandante->setDefaultTextColor(Qt::white);
    textoComandante->setTextWidth(630);
    textoComandante->setPos(65, 65);
    textoComandante->setPlainText(
        "Acércate al comandante para recibir instrucciones."
        );

    iconoTiempoUI = new QGraphicsPixmapItem;
    iconoTiempoUI->setPixmap(
        QPixmap(":/Sprite nivel1/Tiempo.png")
            .scaled(80, 100, Qt::IgnoreAspectRatio, Qt::FastTransformation)
    );
    iconoTiempoUI->setPos(690, 10);
    iconoTiempoUI->setZValue(5);
    addItem(iconoTiempoUI);

    textoTiempo = new QGraphicsTextItem(iconoTiempoUI);
    QFont fuenteTiempo("Arial", 18, QFont::Bold);
    textoTiempo->setFont(fuenteTiempo);
    textoTiempo->setDefaultTextColor(Qt::black);
    textoTiempo->setPos(23, 30);
    textoTiempo->setPlainText("60");
    addItem(textoTiempo);
}

void Nivel1::actualizarFrame()
{
    actualizarCuentaRegresiva();

    if (!estaEnCombate())
        return;

    if (jugador && !jugador->estaMuerta())
    {
        jugador->actualizarMovimiento();
        limitarEntidadEnX(jugador, 40.0f);
        manejarColisionConSuelos();

        if (jugador->obtenerHitbox())
            jugador->obtenerHitbox()->actualizarDesdeEntidad();
    }

    for (Obstaculo *obs : obstaculos)
    {
        if (obs && obs->obtenerHitbox())
            obs->obtenerHitbox()->actualizarDesdeEntidad();
    }

    actualizarTiempo();
    verificarCaida();
    verificarColisionObstaculo();
    verificarInteraccionComandante();
    verificarVictoria();
}

void Nivel1::actualizarTiempo()
{
    if (tiempoRestanteFrames <= 0)
        return;

    --tiempoRestanteFrames;
    int segundos = tiempoRestanteFrames / 60;

    if (textoTiempo)
        textoTiempo->setPlainText(QString("%1").arg(segundos));

    if (tiempoRestanteFrames <= 0)
    {
        marcarDerrota();
        qDebug() << "Nivel 1 perdido por tiempo.";
    }
}

void Nivel1::verificarCaida()
{
    if (!jugador || jugador->estaMuerta())
        return;

    QPointF pos = jugador->obtenerPosicion();
    if (pos.y() > 600)
    {
        marcarDerrota();
        qDebug() << "Nivel 1 perdido: el jugador cayó al vacío.";
    }
}

void Nivel1::verificarVictoria()
{
    if (!jugador || jugador->estaMuerta())
        return;

    if (!zonaMeta)
        return;

    if (!dialogoCompletado)
        return;

    if (zonaMeta->collidesWithItem(jugador))
    {
        marcarVictoria();
        qDebug() << "Nivel 1 completado: el jugador llegó al tanque después de pasar las minas.";
    }
}

void Nivel1::verificarColisionObstaculo()
{
    if (!jugador || jugador->estaMuerta())
        return;

    Hitbox *hbJugador = jugador->obtenerHitbox();
    if (!hbJugador)
        return;

    for (Obstaculo *obs : obstaculos)
    {
        if (!obs)
            continue;

        Hitbox *hbObstaculo = obs->obtenerHitbox();
        if (!hbObstaculo)
            continue;

        if (hbJugador->colisionaCon(hbObstaculo))
        {
            marcarDerrota();
            qDebug() << "Nivel 1 perdido: el jugador tocó una mina.";
            return;
        }
    }
}

void Nivel1::verificarInteraccionComandante()
{
    if (!jugador || jugador->estaMuerta())
        return;
    if (!comandanteVisual)
        return;
    if (dialogoCompletado)
        return;
    if (dialogoIniciado)
        return;

    if (jugador->collidesWithItem(comandanteVisual))
    {
        qDebug() << "Jugador llegó al comandante -> iniciando diálogo";
        iniciarDialogoComandante();
    }
}

void Nivel1::iniciarDialogoComandante()
{
    dialogoIniciado = true;
    dialogoCompletado = false;
    lineasDialogo.clear();
    indiceDialogo = 0;

    lineasDialogo << "Comandante:\nHola, soldado."
                  << "Comandante:\n¿Estás listo para la misión?\n"
                     "Debes saltar las minas y llegar al tanque para llegar al siguiente nivel.\n"
                     "Debes luchar por tu pais, vamos con todo soldado";

    if (!textoComandante)
    {
        textoComandante = new QGraphicsTextItem(panelDialogo);
        QFont fuente("Arial", 14, QFont::Bold);
        textoComandante->setFont(fuente);
        textoComandante->setDefaultTextColor(Qt::white);
        textoComandante->setPos(20, 15);
        addItem(textoComandante);
    }

    textoComandante->setPlainText(lineasDialogo[indiceDialogo]);

    if (timerDialogoComandante)
        timerDialogoComandante->start(2000);
}

void Nivel1::avanzarDialogoComandante()
{
    if (!dialogoIniciado)
        return;

    ++indiceDialogo;

    if (indiceDialogo < lineasDialogo.size())
    {
        textoComandante->setPlainText(lineasDialogo[indiceDialogo]);
    }
    else
    {
        timerDialogoComandante->stop();
        dialogoIniciado = false;
        dialogoCompletado = true;

        textoComandante->setPlainText("Comandante:\n¡Ve al tanque, soldado!");
        qDebug() << "Diálogo con el comandante completado.";
    }
}

void Nivel1::manejarColisionConSuelos()
{
    if (!jugador)
        return;

    QRectF rectJugador = jugador->boundingRect().translated(jugador->pos());
    float alturaJugador = rectJugador.height();
    QPointF pos = jugador->obtenerPosicion();
    bool apoyado = false;

    jugador->establecerEnSuelo(false);

    for (QGraphicsRectItem *suelo : seccionesSuelo)
    {
        if (!suelo)
            continue;

        QRectF rectSuelo = suelo->rect().translated(suelo->pos());

        if (rectJugador.intersects(rectSuelo))
        {
            if (jugador->obtenerVelocidadY() >= 0 &&
                rectJugador.bottom() >= rectSuelo.top() &&
                rectJugador.bottom() <= rectSuelo.top() + 25)
            {
                pos.setY(rectSuelo.top() - alturaJugador);
                jugador->establecerPosicion(pos.x(), pos.y());
                jugador->establecerVelocidad(jugador->obtenerVelocidadX(), 0.0f);
                apoyado = true;
                jugador->establecerEnSuelo(true);
                break;
            }
        }
    }

    if (!apoyado && pos.y() < 600)
        jugador->aplicarGravedad(0.5f);
}

void Nivel1::procesarTeclaPresionada(QKeyEvent *eventoTecla)
{
    if (!jugador || jugador->estaMuerta())
        return;

    if (!estaEnCombate())
        return;

    switch (eventoTecla->key())
    {
    case Qt::Key_A:
    case Qt::Key_Left:
        jugador->moverIzquierda();
        break;

    case Qt::Key_D:
    case Qt::Key_Right:
        jugador->moverDerecha();
        break;

    case Qt::Key_W:
    case Qt::Key_Up:
    case Qt::Key_Space:
        jugador->saltar();
        break;

    default:
        break;
    }
}

void Nivel1::procesarTeclaLiberada(QKeyEvent *eventoTecla)
{
    if (!jugador)
        return;

    if (!estaEnCombate())
        return;

    switch (eventoTecla->key())
    {
    case Qt::Key_A:
    case Qt::Key_Left:
    case Qt::Key_D:
    case Qt::Key_Right:
        jugador->detenerMovimientoHorizontal();
        break;

    default:
        break;
    }
}
