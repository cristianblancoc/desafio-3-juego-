#include "Nivel1.h"
#include "Soldado.h"
#include "Hitbox.h"
#include "obstaculo.h"

#include <QGraphicsRectItem>
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

    QGraphicsRectItem *suelo = new QGraphicsRectItem(0, 550, 800, 50);
    suelo->setBrush(Qt::darkGreen);
    addItem(suelo);
    seccionesSuelo.append(suelo);

    const float width   = 40.0f;
    const float height  = 30.0f;

    obstaculos.append(new Obstaculo(300.0f, 520.0f, width, height));
    obstaculos.append(new Obstaculo(480.0f, 520.0f, width, height));
    obstaculos.append(new Obstaculo(650.0f, 520.0f, width, height));

    for (Obstaculo *o : obstaculos)
        addItem(o);

    zonaMeta = new QGraphicsRectItem(740, 500, 40, 50);
    zonaMeta->setBrush(Qt::blue);
    addItem(zonaMeta);

    comandanteVisual = new QGraphicsRectItem(0, 0, 40, 60);
    if (jugadorEsUcrania)
        comandanteVisual->setBrush(Qt::yellow);
    else
        comandanteVisual->setBrush(Qt::red);

    comandanteVisual->setPos(40, 490);
    addItem(comandanteVisual);
}

void Nivel1::crearJugador()
{
    jugador = new Soldado();

    QPixmap spriteJugador(40, 60);
    if (jugadorEsUcrania)
        spriteJugador.fill(Qt::yellow);
    else
        spriteJugador.fill(Qt::red);

    jugador->setPixmap(spriteJugador);

    jugador->establecerSueloY(500.0f);
    jugador->establecerPosicion(120.0f, 500.0f);
    jugador->establecerVidaMaxima(100.0f);
    jugador->establecerVida(100.0f);
    jugador->establecerModoMovimiento(PersonajeJugador::ModoNivel1);

    jugador->establecerVelocidadMovimiento(4.5f);
    jugador->establecerFuerzaSalto(-20.0f);

    Hitbox *hitboxJugador = new Hitbox(jugador, 40.0f, 60.0f);
    jugador->asignarHitbox(hitboxJugador);

    addItem(jugador);
}

void Nivel1::crearUI()
{
    textoComandante = new QGraphicsTextItem;
    QFont fuente("Arial", 18, QFont::Bold);
    textoComandante->setFont(fuente);
    textoComandante->setDefaultTextColor(Qt::blue);
    textoComandante->setPos(50, 50);
    textoComandante->setPlainText(
        "Acércate al comandante para recibir instrucciones."
        );
    addItem(textoComandante);

    textoTiempo = new QGraphicsTextItem;
    QFont fuenteTiempo("Arial", 16, QFont::Bold);
    textoTiempo->setFont(fuenteTiempo);
    textoTiempo->setDefaultTextColor(Qt::darkRed);
    textoTiempo->setPos(600, 20);
    textoTiempo->setPlainText("Tiempo: 60");
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
        textoTiempo->setPlainText(QString("Tiempo: %1").arg(segundos));

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

    // Solo se puede ganar si ya se completó el diálogo con el comandante
    if (!dialogoCompletado)
        return;

    if (zonaMeta->collidesWithItem(jugador))
    {
        marcarVictoria();
        qDebug() << "Nivel 1 completado: el jugador llegó a la zona azul después del briefing.";
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
            qDebug() << "Nivel 1 perdido: el jugador tocó un obstáculo.";
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
                     "Debes saltar las cajas y llegar a la zona azul para continuar.";

    if (!textoComandante)
    {
        textoComandante = new QGraphicsTextItem;
        QFont fuente("Arial", 18, QFont::Bold);
        textoComandante->setFont(fuente);
        textoComandante->setDefaultTextColor(Qt::blue);
        textoComandante->setPos(50, 50);
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

        textoComandante->setPlainText("Comandante:\n¡Ve a la zona azul, soldado!");
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
