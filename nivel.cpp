#include "Nivel.h"
#include "Entidad.h"

#include <QKeyEvent>
#include <QDebug>

Nivel::Nivel(int numeroNivel, QObject *parent)
    : QGraphicsScene(parent)
    , numeroNivel(numeroNivel)
    , temporizador(new QTimer(this))
    , milisegundosPorFrame(16)
    , enCombate(true)
    , textoCuentaRegresiva(nullptr)
    , segundosRestantes(0)
    , contadorFramesCuenta(0)
    , framesPorSegundo(60)
    , textoResultado(nullptr)
    , resultadoMostrado(false)
{
    connect(temporizador, &QTimer::timeout,
            this, &Nivel::onActualizarFrame);
}

Nivel::~Nivel() {}


void Nivel::iniciarTemporizador()
{
    if (temporizador)
        temporizador->start(milisegundosPorFrame);
}

void Nivel::detenerTemporizador()
{
    if (temporizador)
        temporizador->stop();
}

void Nivel::onActualizarFrame()
{
    actualizarFrame();
}

void Nivel::keyPressEvent(QKeyEvent *eventoTecla)
{
    procesarTeclaPresionada(eventoTecla);
    QGraphicsScene::keyPressEvent(eventoTecla);
}

void Nivel::keyReleaseEvent(QKeyEvent *eventoTecla)
{
    procesarTeclaLiberada(eventoTecla);
    QGraphicsScene::keyReleaseEvent(eventoTecla);
}

void Nivel::prepararCuentaRegresiva(int segundos)
{
    segundosRestantes = segundos;
    enCombate = false;
    contadorFramesCuenta = 0;

    if (!textoCuentaRegresiva)
    {
        textoCuentaRegresiva = new QGraphicsTextItem;
        addItem(textoCuentaRegresiva);
        QFont fuente("Arial", 24, QFont::Bold);
        textoCuentaRegresiva->setFont(fuente);
        textoCuentaRegresiva->setDefaultTextColor(Qt::red);
        textoCuentaRegresiva->setPos(300, 50);
    }

    textoCuentaRegresiva->setPlainText(
        QString("Inicia en: %1").arg(segundosRestantes));
    textoCuentaRegresiva->setVisible(true);
}

void Nivel::actualizarCuentaRegresiva()
{
    if (segundosRestantes <= 0)
        return;

    ++contadorFramesCuenta;

    if (contadorFramesCuenta < framesPorSegundo)
        return;

    contadorFramesCuenta = 0;
    --segundosRestantes;

    if (textoCuentaRegresiva)
    {
        if (segundosRestantes > 0)
        {
            textoCuentaRegresiva->setPlainText(
                QString("Inicia en: %1").arg(segundosRestantes));
        }
        else
        {
            textoCuentaRegresiva->setVisible(false);
        }
    }

    if (segundosRestantes == 0)
        enCombate = true;
}

bool Nivel::estaEnCombate() const
{
    return enCombate;
}

int Nivel::obtenerNumeroNivel() const
{
    return numeroNivel;
}

void Nivel::limitarEntidadEnX(Entidad *entidad, float anchoSprite)
{
    if (!entidad)
        return;

    QRectF rect = sceneRect();
    QPointF pos = entidad->obtenerPosicion();

    float minX = rect.left();
    float maxX = rect.right() - anchoSprite;

    if (pos.x() < minX)
        pos.setX(minX);
    else if (pos.x() > maxX)
        pos.setX(maxX);

    entidad->establecerPosicion(pos.x(), pos.y());
}

void Nivel::marcarVictoria()
{
    if (resultadoMostrado)
        return;

    resultadoMostrado = true;
    detenerTemporizador();
    enCombate = false;

    if (!textoResultado)
    {
        textoResultado = new QGraphicsTextItem;
        addItem(textoResultado);
        QFont fuente("Arial", 32, QFont::Bold);
        textoResultado->setFont(fuente);
        textoResultado->setPos(260, 260);
    }

    textoResultado->setDefaultTextColor(Qt::green);
    textoResultado->setPlainText("GANASTE");
    textoResultado->setVisible(true);

    emit nivelGanado(numeroNivel);
}

void Nivel::marcarDerrota()
{
    if (resultadoMostrado)
        return;

    resultadoMostrado = true;
    detenerTemporizador();
    enCombate = false;

    if (!textoResultado)
    {
        textoResultado = new QGraphicsTextItem;
        addItem(textoResultado);
        QFont fuente("Arial", 32, QFont::Bold);
        textoResultado->setFont(fuente);
        textoResultado->setPos(260, 260);
    }

    textoResultado->setDefaultTextColor(Qt::red);
    textoResultado->setPlainText("PERDISTE");
    textoResultado->setVisible(true);

    emit nivelPerdido(numeroNivel);
}
