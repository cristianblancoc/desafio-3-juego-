#include "Nivel3.h"
#include "Hitbox.h"
#include "Soldado.h"
#include "EnemigoSoldadoIA.h"
#include "proyectiln3.h"
#include "entidad.h"

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QFont>
#include <QDebug>
#include <QtMath>

// Vida base
static const float VIDA_INICIAL_JUGADOR = 300.0f;
static const float VIDA_INICIAL_ENEMIGO = 300.0f;

// Número de vidas (respawns)
static const int VIDAS_INICIALES_JUGADOR = 3;
static const int VIDAS_INICIALES_ENEMIGO = 3;

// Tiempo de combate (segundos)
static const int TIEMPO_COMBATE_INICIAL = 60;

// Velocidades
static const float VELOCIDAD_JUGADOR = 3.5f;
static const float VELOCIDAD_ENEMIGO = 1.8f;

// Proyectiles jugador
static const float VELOCIDAD_PROYECTIL_JUGADOR = 8.0f;
static const float DANO_PROYECTIL_JUGADOR      = 12.0f;

// Proyectiles enemigo
static const float VELOCIDAD_PROYECTIL_ENEMIGO = 8.0f;
static const float DANO_PROYECTIL_ENEMIGO      = 12.0f;

// IA enemigo
static const float DISTANCIA_DETECCION_ENEMIGO = 700.0f;
static const int   CUADROS_ENTRE_DISPAROS_ENEMIGO = 45;

Nivel3::Nivel3(QObject *parent)
    : Nivel(3, parent)
    , jugador(nullptr)
    , jugadorEsUcrania(true)
    , vidasJugador(VIDAS_INICIALES_JUGADOR)
    , vidasEnemigo(VIDAS_INICIALES_ENEMIGO)
    , textoVidas(nullptr)
    , tiempoCombateSegundos(TIEMPO_COMBATE_INICIAL)
    , contadorFramesTiempo(0)
    , textoTiempo(nullptr)
    , combateFinalizado(false)
    , barraVidaJugadorFondo(nullptr)
    , barraVidaJugadorRelleno(nullptr)
    , barraVidaEnemigoFondo(nullptr)
    , barraVidaEnemigoRelleno(nullptr)
    , labelVidaJugador(nullptr)
    , labelVidaEnemigo(nullptr)
    , iconoTiempo(nullptr)
    , fondoResultado(nullptr)
    , jugadorEstabaMuerto(false)
{
}

void Nivel3::establecerBandoJugadorUcrania(bool esUcrania)
{
    jugadorEsUcrania = esUcrania;
}

void Nivel3::iniciarNivel()
{
    clear();

    vidasJugador = VIDAS_INICIALES_JUGADOR;
    vidasEnemigo = VIDAS_INICIALES_ENEMIGO;
    tiempoCombateSegundos = TIEMPO_COMBATE_INICIAL;
    contadorFramesTiempo = 0;
    combateFinalizado = false;

    barraVidaJugadorFondo = nullptr;
    barraVidaJugadorRelleno = nullptr;
    barraVidaEnemigoFondo = nullptr;
    barraVidaEnemigoRelleno = nullptr;
    labelVidaJugador = nullptr;
    labelVidaEnemigo = nullptr;
    iconoTiempo = nullptr;
    fondoResultado = nullptr;
    jugadorEstabaMuerto = false;

    crearEscenario();
    crearJugador();
    crearEnemigos();
    crearUI();

    textoVidas = addText(QString(), QFont("Arial", 14, QFont::Bold));
    textoVidas->setDefaultTextColor(Qt::white);
    textoVidas->setPos(10, 95);

    iconoTiempo = new QGraphicsPixmapItem;
    iconoTiempo->setPixmap(
        QPixmap(":/Sprite nivel3/Tiempo.png")
            .scaled(80, 100, Qt::IgnoreAspectRatio, Qt::FastTransformation)
        );
    iconoTiempo->setPos(360, 5);
    iconoTiempo->setZValue(5);
    addItem(iconoTiempo);

    textoTiempo = new QGraphicsTextItem(iconoTiempo);
    QFont fuenteTiempo("Arial", 18, QFont::Bold);
    textoTiempo->setFont(fuenteTiempo);
    textoTiempo->setDefaultTextColor(Qt::black);
    textoTiempo->setPos(23, 30);
    actualizarTextoTiempo();


    actualizarTextoVidas();
    actualizarBarraVida();

    prepararCuentaRegresiva(5);

    qDebug() << "Nivel 3 iniciado.";
}

void Nivel3::crearEscenario()
{
    setSceneRect(0, 0, 800, 600);

    QString rutaFondo = ":/Sprite nivel3/Fondo_nivel3.png";
    QPixmap fondo(rutaFondo);

    if (!fondo.isNull())
    {
        QGraphicsPixmapItem *fondoItem =
            new QGraphicsPixmapItem(
                fondo.scaled(sceneRect().size().toSize(),
                             Qt::IgnoreAspectRatio,
                             Qt::SmoothTransformation));

        fondoItem->setPos(0, 0);
        fondoItem->setZValue(-1000);
        addItem(fondoItem);
    }
    else
    {
        qDebug() << "No se pudo cargar el fondo de Nivel 3";
    }

    // Suelo
    QGraphicsRectItem *suelo = new QGraphicsRectItem(0, 400, 800, 50);
    suelo->setVisible(false);
    suelo->setZValue(10);
    addItem(suelo);

}

void Nivel3::crearJugador()
{
    jugador = new Soldado();

    if (jugadorEsUcrania)
    {
        jugador->establecerSprites(
            ":/Sprite nivel1/Soldado Ukrania Estatico.png",
            ":/Sprite nivel3/Soldado Ukrania disparando derecha.png",
            ":/Sprite nivel3/Soldado Ukrania disparando izquierda.png",
            ":/Sprite nivel1/Soldado Ukrania Saltando derecha.png",
            ":/Sprite nivel1/Soldado Ukrania Saltando izquierda.png"

            );

        jugador->establecerSpritesDisparo(
            ":/Sprite nivel3/Soldado Ukrania disparando derecha.png",
            ":/Sprite nivel3/Soldado Ukrania disparando izquierda.png"
            );
    }
    else
    {
        jugador->establecerSprites(
            ":/Sprite nivel1/Soldado Russia Estatico.png",
            ":/Sprite nivel3/Soldado Russia Disparando Derecha.png",
            ":/Sprite nivel3/Soldado Russia Disparando Izquierda.png",
            ":/Sprite nivel1/Soldado Russia Saltando Derecha.png",
            ":/Sprite nivel1/Soldado Russia Saltando Izquierda.png"

            );

        jugador->establecerSpritesDisparo(
            ":/Sprite nivel3/Soldado Russia Disparando Derecha.png",
            ":/Sprite nivel3/Soldado Russia Disparando Izquierda.png"
            );
    }

    jugador->establecerSueloY(400.0f);
    jugador->establecerPosicion(120.0f, 390.0f);
    jugador->establecerVidaMaxima(VIDA_INICIAL_JUGADOR);
    jugador->establecerVida(VIDA_INICIAL_JUGADOR);
    jugador->establecerModoMovimiento(PersonajeJugador::ModoNivel3);
    jugador->establecerVelocidadMovimiento(VELOCIDAD_JUGADOR);

    Hitbox *hitboxJugador = new Hitbox(jugador, 40.0f, 60.0f);
    jugador->asignarHitbox(hitboxJugador);

    addItem(jugador);
}

void Nivel3::crearEnemigos()
{
    for (EnemigoSoldadoIA *e : enemigos)
    {
        if (e)
            e->deleteLater();
    }
    enemigos.clear();
    tiempoDisparoEnemigos.clear();

    EnemigoSoldadoIA *enemigo = new EnemigoSoldadoIA();

    bool enemigoEsUcrania = !jugadorEsUcrania;

    if (enemigoEsUcrania)
    {
        enemigo->establecerSprites(
            ":/Sprite nivel1/Soldado Ukrania Estatico.png",
            ":/Sprite nivel3/Soldado Ukrania disparando derecha.png",
            ":/Sprite nivel3/Soldado Ukrania disparando izquierda.png",
            ":/Sprite nivel1/Soldado Ukrania Saltando derecha.png",
            ":/Sprite nivel1/Soldado Ukrania Saltando izquierda.png",
            ":/Sprite nivel3/Soldado Ukrania disparando derecha.png",
            ":/Sprite nivel3/Soldado Ukrania disparando izquierda.png"
            );
    }
    else
    {
        enemigo->establecerSprites(
            ":/Sprite nivel1/Soldado Russia Estatico.png",
            ":/Sprite nivel3/Soldado Russia Disparando Derecha.png",
            ":/Sprite nivel3/Soldado Russia Disparando Izquierda.png",
            ":/Sprite nivel1/Soldado Russia Saltando Derecha.png",
            ":/Sprite nivel1/Soldado Russia Saltando Izquierda.png",
            ":/Sprite nivel3/Soldado Russia Disparando Derecha.png",
            ":/Sprite nivel3/Soldado Russia Disparando Izquierda.png"
            );
    }

    enemigo->establecerSueloY(400.0f);
    enemigo->establecerPosicion(600.0f, 390.0f);
    enemigo->establecerVidaMaxima(VIDA_INICIAL_ENEMIGO);
    enemigo->establecerVida(VIDA_INICIAL_ENEMIGO);

    enemigo->establecerObjetivo(jugador);
    enemigo->establecerDistanciaDeteccion(DISTANCIA_DETECCION_ENEMIGO);
    enemigo->establecerVelocidadMovimiento(VELOCIDAD_ENEMIGO);
    enemigo->establecerCuadrosEntreAtaques(CUADROS_ENTRE_DISPAROS_ENEMIGO);

    Hitbox *hitboxEnemigo = new Hitbox(enemigo, 40.0f, 60.0f);
    enemigo->asignarHitbox(hitboxEnemigo);

    addItem(enemigo);
    enemigos.append(enemigo);
    tiempoDisparoEnemigos.append(0);

    actualizarBarraVidaEnemigo();
}

void Nivel3::crearUI()
{

    int yUI = 60;
    const int anchoBarra = 200;
    const int altoBarra = 18;
    const int margen = 10;

    qreal anchoEscena = sceneRect().width();
    if (anchoEscena <= 0)
        anchoEscena = 800;

    // Barra vida jugador (izquierda)
    barraVidaJugadorFondo = new QGraphicsRectItem(0, 0, anchoBarra, altoBarra);
    barraVidaJugadorFondo->setBrush(QColor(80, 80, 80));
    barraVidaJugadorFondo->setPen(QPen(Qt::black));
    barraVidaJugadorFondo->setPos(margen, yUI);
    addItem(barraVidaJugadorFondo);

    barraVidaJugadorRelleno = new QGraphicsRectItem(0, 0, anchoBarra, altoBarra, barraVidaJugadorFondo);
    barraVidaJugadorRelleno->setBrush(Qt::red);
    barraVidaJugadorRelleno->setPen(Qt::NoPen);

    // Barra vida enemigo (derecha)
    barraVidaEnemigoFondo = new QGraphicsRectItem(0, 0, anchoBarra, altoBarra);
    barraVidaEnemigoFondo->setBrush(QColor(80, 80, 80));
    barraVidaEnemigoFondo->setPen(QPen(Qt::black));
    barraVidaEnemigoFondo->setPos(anchoEscena - anchoBarra - margen, yUI);
    addItem(barraVidaEnemigoFondo);

    barraVidaEnemigoRelleno = new QGraphicsRectItem(0, 0, anchoBarra, altoBarra, barraVidaEnemigoFondo);
    barraVidaEnemigoRelleno->setBrush(Qt::red);
    barraVidaEnemigoRelleno->setPen(Qt::NoPen);

    // Labels de país encima de cada barra
    QString nombrePaisJugador = jugadorEsUcrania ? "Ucrania" : "Rusia";
    QString nombrePaisEnemigo = jugadorEsUcrania ? "Rusia"   : "Ucrania";

    labelVidaJugador = addText(nombrePaisJugador, QFont("Arial", 12, QFont::Bold));
    labelVidaEnemigo = addText(nombrePaisEnemigo, QFont("Arial", 12, QFont::Bold));

    labelVidaJugador->setDefaultTextColor(Qt::white);
    labelVidaEnemigo->setDefaultTextColor(Qt::white);

    labelVidaJugador->setPos(margen, yUI - 22);
    labelVidaEnemigo->setPos(anchoEscena - anchoBarra - margen, yUI - 22);
}

void Nivel3::actualizarBarraVida()
{
    actualizarBarraVidaJugador();
    actualizarBarraVidaEnemigo();
}

void Nivel3::actualizarBarraVidaJugador()
{
    if (!jugador || !barraVidaJugadorFondo || !barraVidaJugadorRelleno)
        return;

    float vidaActual = jugador->obtenerVida();
    float vidaMax = jugador->obtenerVidaMaxima();
    if (vidaMax <= 0.0f)
        vidaMax = 1.0f;

    float factor = vidaActual / vidaMax;
    factor = qBound(0.0f, factor, 1.0f);

    QRectF rectFondo = barraVidaJugadorFondo->rect();
    float nuevoAncho = rectFondo.width() * factor;

    barraVidaJugadorRelleno->setRect(0, 0, nuevoAncho, rectFondo.height());
}

void Nivel3::actualizarBarraVidaEnemigo()
{
    if (enemigos.isEmpty())
        return;

    EnemigoSoldadoIA *enemigo = enemigos.first();
    if (!enemigo || enemigo->estaEliminado())
        return;

    if (!barraVidaEnemigoFondo || !barraVidaEnemigoRelleno)
        return;

    float vidaActual = enemigo->obtenerVida();
    float vidaMax = enemigo->obtenerVidaMaxima();
    if (vidaMax <= 0.0f)
        vidaMax = 1.0f;

    float factor = vidaActual / vidaMax;
    factor = qBound(0.0f, factor, 1.0f);

    QRectF rectFondo = barraVidaEnemigoFondo->rect();
    float nuevoAncho = rectFondo.width() * factor;

    barraVidaEnemigoRelleno->setRect(0, 0, nuevoAncho, rectFondo.height());
}

void Nivel3::actualizarFrame()
{
    if (combateFinalizado)
        return;

    actualizarCuentaRegresiva();

    if (!estaEnCombate())
        return;

    if (tiempoCombateSegundos > 0)
    {
        contadorFramesTiempo++;
        if (contadorFramesTiempo >= 60)
        {
            contadorFramesTiempo = 0;
            tiempoCombateSegundos--;
            actualizarTextoTiempo();

            if (tiempoCombateSegundos <= 0)
            {
                manejarFinPorTiempo();
                return;
            }
        }
    }

    if (jugador && !jugador->estaMuerta())
    {
        jugador->actualizarMovimiento();
        limitarEntidadEnX(jugador, 40.0f);
    }

    for (int i = 0; i < enemigos.size(); ++i)
    {
        EnemigoSoldadoIA *enemigo = enemigos[i];
        if (!enemigo || enemigo->estaEliminado())
            continue;

        enemigo->actualizarIA();
        limitarEntidadEnX(enemigo, 40.0f);

        if (tiempoDisparoEnemigos[i] > 0)
            --tiempoDisparoEnemigos[i];

        if (!jugador || jugador->estaMuerta())
            continue;

        QPointF posJugador = jugador->obtenerPosicion();
        QPointF posEnemigo = enemigo->obtenerPosicion();
        float dx = posJugador.x() - posEnemigo.x();
        float distanciaX = qFabs(dx);

        if (distanciaX < 500.0f && tiempoDisparoEnemigos[i] <= 0)
        {
            crearProyectilEnemigo(enemigo);
            tiempoDisparoEnemigos[i] = CUADROS_ENTRE_DISPAROS_ENEMIGO;
        }
    }

    for (EnemigoSoldadoIA *enemigo : enemigos)
    {
        if (!enemigo || enemigo->estaEliminado())
            continue;

        QPointF posEnemigo = enemigo->obtenerPosicion();

        for (ProyectilN3 *p : proyectilesJugador)
        {
            if (!p || !p->estaActivo())
                continue;

            QPointF posP = p->pos();
            float dx = qAbs(posP.x() - posEnemigo.x());
            float dy = qAbs(posP.y() - posEnemigo.y());

            if (dx < 80.0f && dy < 40.0f)
            {
                enemigo->saltar();
                break;
            }
        }
    }

    resolverColisionJugadorEnemigos();

    limitarEntidadEnX(jugador, jugador->boundingRect().width());
    for (EnemigoSoldadoIA *enemigo : enemigos)
    {
        if (!enemigo || enemigo->estaEliminado())
            continue;
        limitarEntidadEnX(enemigo, enemigo->boundingRect().width());
    }

    actualizarProyectilesJugador();
    actualizarProyectilesEnemigos();

    verificarColisionesProyectilesConEnemigos();
    verificarColisionesProyectilesEnemigosConJugador();

    gestionarMuerteJugador();

    bool estaMuertoAhora = (jugador && jugador->estaMuerta());
    if (estaMuertoAhora && !jugadorEstabaMuerto)
    {
        gestionarMuerteJugador();
    }
    jugadorEstabaMuerto = estaMuertoAhora;


}

void Nivel3::actualizarProyectilesJugador()
{
    for (ProyectilN3 *p : proyectilesJugador)
    {
        if (!p)
            continue;

        if (p->estaActivo())
            p->actualizarProyectil();
    }
}

void Nivel3::actualizarProyectilesEnemigos()
{
    for (ProyectilN3 *p : proyectilesEnemigos)
    {
        if (!p)
            continue;

        if (p->estaActivo())
            p->actualizarProyectil();
    }
}

void Nivel3::verificarColisionesProyectilesConEnemigos()
{
    for (ProyectilN3 *p : proyectilesJugador)
    {
        if (!p || !p->estaActivo())
            continue;

        Hitbox *hbProyectil = p->obtenerHitbox();
        if (!hbProyectil)
            continue;

        for (EnemigoSoldadoIA *enemigo : enemigos)
        {
            if (!enemigo || enemigo->estaEliminado())
                continue;

            Hitbox *hbEnemigo = enemigo->obtenerHitbox();
            if (!hbEnemigo)
                continue;

            if (hbProyectil->colisionaCon(hbEnemigo))
            {
                enemigo->recibirDano(p->obtenerDano());

                p->establecerVida(0);
                p->setVisible(false);

                actualizarBarraVidaEnemigo();

                qDebug() << "Enemigo impactado. Vida enemigo:" << enemigo->obtenerVida();

                if (enemigo->estaMuerta())
                {
                    enemigo->marcarEliminado();
                    enemigo->setVisible(false);
                    qDebug() << "Enemigo eliminado por proyectil del jugador.";

                    vidasEnemigo--;
                    actualizarTextoVidas();

                    if (vidasEnemigo <= 0)
                    {
                        marcarVictoria();
                    }
                    else
                    {
                        crearEnemigos();
                    }
                }

                break;
            }
        }
    }
}

void Nivel3::verificarColisionesProyectilesEnemigosConJugador()
{
    if (!jugador || jugador->estaMuerta())
        return;

    Hitbox *hbJugador = jugador->obtenerHitbox();
    if (!hbJugador)
        return;

    for (ProyectilN3 *p : proyectilesEnemigos)
    {
        if (!p || !p->estaActivo())
            continue;

        Hitbox *hbProyectil = p->obtenerHitbox();
        if (!hbProyectil)
            continue;

        if (hbProyectil->colisionaCon(hbJugador))
        {
            jugador->recibirDano(p->obtenerDano());

            p->establecerVida(0);
            p->setVisible(false);

            actualizarBarraVidaJugador();

            qDebug() << "Jugador impactado por proyectil enemigo. Vida jugador:"
                     << jugador->obtenerVida();
        }
    }
}

void Nivel3::procesarTeclaPresionada(QKeyEvent *eventoTecla)
{
    if (combateFinalizado)
        return;

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
        jugador->saltar();
        break;

    case Qt::Key_Space:
        jugador->empezarDisparo();
        crearProyectilJugador();
        break;

    default:
        break;
    }
}

void Nivel3::procesarTeclaLiberada(QKeyEvent *eventoTecla)
{
    if (combateFinalizado)
        return;

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

    case Qt::Key_Space:
        jugador->detenerDisparo();
        break;

    default:
        break;
    }
}

void Nivel3::crearProyectilJugador()
{
    if (!jugador || jugador->estaMuerta())
        return;

    QPointF posJugador = jugador->obtenerPosicion();
    int dir = jugador->obtenerDireccion();

    float origenX = posJugador.x() + 25.0f * dir;
    float origenY = posJugador.y() + 20.0f;

    ProyectilN3 *p = new ProyectilN3(
        dir,
        origenX,
        origenY,
        VELOCIDAD_PROYECTIL_JUGADOR,
        DANO_PROYECTIL_JUGADOR
        );

    if (dir == 1)
    {
        p->establecerSprite(":/Sprite nivel3/Bala derecha.png");
    }
    else
    {
        p->establecerSprite(":/Sprite nivel3/Bala izquierda.png");
    }

    addItem(p);
    proyectilesJugador.append(p);
}

void Nivel3::crearProyectilEnemigo(EnemigoSoldadoIA *enemigo)
{
    if (!enemigo || enemigo->estaEliminado())
        return;

    if (!jugador)
        return;

    QPointF posEnemigo = enemigo->obtenerPosicion();
    QPointF posJugador = jugador->obtenerPosicion();

    int dir = (posJugador.x() < posEnemigo.x()) ? -1 : 1;

    float origenX = posEnemigo.x() + 20.0f * dir;
    float origenY = posEnemigo.y() + 20.0f;

    ProyectilN3 *p = new ProyectilN3(
        dir,
        origenX,
        origenY,
        VELOCIDAD_PROYECTIL_ENEMIGO,
        DANO_PROYECTIL_ENEMIGO
        );

    if (dir == 1)
    {
        p->establecerSprite(":/Sprite nivel3/Bala derecha.png");
    }
    else
    {
        p->establecerSprite(":/Sprite nivel3/Bala izquierda.png");
    }

    addItem(p);
    proyectilesEnemigos.append(p);

    qDebug() << "Enemigo disparó proyectil.";
}

void Nivel3::gestionarMuerteJugador()
{
    if (!jugador || !jugador->estaMuerta() || !estaEnCombate())
        return;

    qDebug() << "gestionarMuerteJugador - vidasJugador (antes):" << vidasJugador;

    if (vidasJugador > 1)
    {
        vidasJugador--;
        reiniciarRonda();
        actualizarTextoVidas();
        qDebug() << "Jugador perdió una vida. Vidas restantes:" << vidasJugador;
    }
    else
    {
        marcarDerrota();
        qDebug() << "Jugador sin vidas. Derrota.";
    }
}

void Nivel3::actualizarTextoVidas()
{
    if (textoVidas)
    {
        textoVidas->setPlainText(
            QString("Vidas J: %1 | Vidas E: %2")
                .arg(vidasJugador)
                .arg(vidasEnemigo)
            );
    }
}

void Nivel3::actualizarTextoTiempo()
{
    if (textoTiempo)
        textoTiempo->setPlainText(QString("%1").arg(tiempoCombateSegundos));
}

void Nivel3::manejarFinPorTiempo()
{
    if (combateFinalizado)
        return;

    bool enemigoSigueVivo = false;
    for (EnemigoSoldadoIA *e : enemigos)
    {
        if (e && !e->estaEliminado())
        {
            enemigoSigueVivo = true;
            break;
        }
    }

    if (enemigoSigueVivo || vidasEnemigo > 0)
    {
        marcarDerrota();
        qDebug() << "Tiempo agotado. El jugador pierde.";
    }
    else
    {
        marcarVictoria();
        qDebug() << "Tiempo agotado, pero el enemigo ya estaba derrotado.";
    }
}

void Nivel3::resolverColisionJugadorEnemigos()
{
    if (!jugador || jugador->estaMuerta())
        return;


    QRectF rectEscena = sceneRect();

    float anchoJugador = jugador->boundingRect().width();

    const float margenIzq = 10.0f;
    const float margenDer = 10.0f;

    float minX = rectEscena.left() + margenIzq;
    float maxX = rectEscena.right() - anchoJugador - margenDer;

    QRectF rectJugador = jugador->boundingRect().translated(jugador->pos());

    for (EnemigoSoldadoIA *enemigo : enemigos)
    {
        if (!enemigo || enemigo->estaEliminado())
            continue;

        QRectF rectEnemigo = enemigo->boundingRect().translated(enemigo->pos());

        if (!rectJugador.intersects(rectEnemigo))
            continue;

        QPointF posJugador = jugador->obtenerPosicion();

        if (rectJugador.center().x() < rectEnemigo.center().x())
        {
            posJugador.setX(rectEnemigo.left() - rectJugador.width());
        }
        else
        {
            posJugador.setX(rectEnemigo.right());
        }

        if (posJugador.x() < minX)
            posJugador.setX(minX);
        else if (posJugador.x() > maxX)
            posJugador.setX(maxX);

        jugador->establecerPosicion(posJugador.x(), posJugador.y());
        rectJugador = jugador->boundingRect().translated(jugador->pos());
    }
}

void Nivel3::marcarVictoria()
{
    if (combateFinalizado)
        return;

    combateFinalizado = true;

    mostrarFondoResultado(true);

    emit nivelGanado(obtenerNumeroNivel());
}

void Nivel3::marcarDerrota()
{
    if (combateFinalizado)
        return;

    combateFinalizado = true;

    mostrarFondoResultado(false);

    //emit nivelPerdido(obtenerNumeroNivel());
}

void Nivel3::limitarEntidadEnX_N3(Entidad *entidad, float anchoSprite)
{
    if (!entidad)
        return;

    QRectF rect = sceneRect();
    QPointF pos = entidad->obtenerPosicion();

    float margenLateral = 10.0f;
    float minX = rect.left()  + margenLateral;
    float maxX = rect.right() - margenLateral - anchoSprite;

    if (pos.x() < minX)
        pos.setX(minX);
    else if (pos.x() > maxX)
        pos.setX(maxX);

    entidad->establecerPosicion(pos.x(), pos.y());
}

void Nivel3::mostrarFondoResultado(bool jugadorGana)
{
    QString ruta;

    if (jugadorEsUcrania)
    {
        if (jugadorGana)
            ruta = ":/Sprite nivel3/Victoria_Ukrania.png";
        else
            ruta = ":/Sprite nivel3/Derrota_Ukrania.png";
    }
    else
    {
        if (jugadorGana)
            ruta = ":/Sprite nivel3/Victoria_Russia.png";
        else
            ruta = ":/Sprite nivel3/Derrota_Russia.png";
    }

    QPixmap img(ruta);
    if (img.isNull())
    {
        qDebug() << "No se pudo cargar fondo de resultado:" << ruta;
        return;
    }

    fondoResultado = new QGraphicsPixmapItem(
        img.scaled(800, 600,
                   Qt::IgnoreAspectRatio,
                   Qt::SmoothTransformation));
    fondoResultado->setPos(0, 0);
    fondoResultado->setZValue(1000);
    addItem(fondoResultado);
}

void Nivel3::reiniciarRonda()
{
    if (jugador)
    {
        jugador->establecerVida(VIDA_INICIAL_JUGADOR);
        jugador->establecerPosicion(120.0f, 390.0f);
        jugador->setVisible(true);
        jugador->detenerMovimientoHorizontal();
    }

    for (EnemigoSoldadoIA *enemigo : enemigos)
    {
        if (!enemigo || enemigo->estaEliminado())
            continue;

        enemigo->establecerVida(VIDA_INICIAL_ENEMIGO);
        enemigo->establecerPosicion(600.0f, 390.0f);
        enemigo->setVisible(true);
    }

    for (ProyectilN3 *p : proyectilesJugador)
    {
        if (!p) continue;
        p->establecerVida(0);
        p->setVisible(false);
    }
    proyectilesJugador.clear();

    for (ProyectilN3 *p : proyectilesEnemigos)
    {
        if (!p) continue;
        p->establecerVida(0);
        p->setVisible(false);
    }
    proyectilesEnemigos.clear();

    for (int i = 0; i < tiempoDisparoEnemigos.size(); ++i)
    {
        tiempoDisparoEnemigos[i] = 0;
    }
    actualizarBarraVidaJugador();
    actualizarBarraVidaEnemigo();
}
