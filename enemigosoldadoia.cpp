#include "enemigosoldadoia.h"
#include "Hitbox.h"
#include <QtMath>
#include <QDebug>

EnemigoSoldadoIA::EnemigoSoldadoIA(QGraphicsItem *parent)
    : Enemigo(parent)
    , objetivo(nullptr)
    , distanciaDeteccion(300)
    , velocidadMovimientoIA(2)
    , cuadrosEntreAtaques(30)
    , contadorCuadrosAtaque(0)
    , direccion(-1)
    , disparando(false)
    , contadorDisparoFrames(0)
    , cuadrosQuietoAntesMover(120)
    , contadorQuieto(0)
    , puedeMoverse(false)
{
    establecerFuerzaSalto(-12.0f);
}

void EnemigoSoldadoIA::establecerObjetivo(Entidad *nuevoObjetivo)
{
    objetivo = nuevoObjetivo;
}

void EnemigoSoldadoIA::establecerDistanciaDeteccion(float nuevaDistancia)
{
    distanciaDeteccion = nuevaDistancia;
}

void EnemigoSoldadoIA::establecerVelocidadMovimiento(float nuevaVelocidad)
{
    velocidadMovimientoIA = nuevaVelocidad;
}

void EnemigoSoldadoIA::establecerCuadrosEntreAtaques(int cuadros)
{
    cuadrosEntreAtaques = cuadros;
}

void EnemigoSoldadoIA::establecerSprites(
    const QString &estatico,
    const QString &correrDer,
    const QString &correrIzq,
    const QString &saltarDer,
    const QString &saltarIzq,
    const QString &dispararDer,
    const QString &dispararIzq
    ){
    spriteEstatico          = QPixmap(estatico);
    spriteCorrerDerecha     = QPixmap(correrDer);
    spriteCorrerIzquierda   = QPixmap(correrIzq);
    spriteSaltarDerecha     = QPixmap(saltarDer);
    spriteSaltarIzquierda   = QPixmap(saltarIzq);
    spriteDispararDerecha   = QPixmap(dispararDer);
    spriteDispararIzquierda = QPixmap(dispararIzq);

    if (!spriteEstatico.isNull())
        setPixmap(spriteEstatico.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void EnemigoSoldadoIA::notificarDisparo(int dir)
{
    disparando = true;
    contadorDisparoFrames = 10;
    direccion = (dir >= 0) ? 1 : -1;
}

void EnemigoSoldadoIA::actualizarIA()
{
    if (estaEliminado() || !objetivo || objetivo->estaMuerta())
    {
        velocidadX = 0.0f;

        actualizarMovimientoBasico();
        actualizarSprite();
        return;
    }

    if (!puedeMoverse)
    {
        contadorQuieto++;
        if (contadorQuieto >= cuadrosQuietoAntesMover)
            puedeMoverse = true;
    }

    ejecutarMovimientoIA();
    actualizarMovimientoBasico();
    intentarAtacar();
    actualizarSprite();
}

void EnemigoSoldadoIA::ejecutarMovimientoIA()
{
    if (!objetivo)
        return;

    float dx = objetivo->obtenerPosicion().x() - obtenerPosicion().x();
    float distancia = qAbs(dx);

    if (!puedeMoverse)
    {
        velocidadX = 0.0f;
        if (dx < 0) direccion = -1; else if (dx > 0) direccion = 1;
        return;
    }

    if (distancia > distanciaDeteccion)
    {
        velocidadX = 0.0f;
        return;
    }

    if (dx < -1)
    {
        velocidadX = -velocidadMovimientoIA;
        direccion = -1;
    }
    else if (dx > 1)
    {
        velocidadX = velocidadMovimientoIA;
        direccion = 1;
    }
    else
    {
        velocidadX = 0.0f;
    }
}

void EnemigoSoldadoIA::intentarAtacar()
{
    if (!objetivo || estaEliminado() || objetivo->estaMuerta())
        return;

    if (contadorCuadrosAtaque > 0)
    {
        contadorCuadrosAtaque--;
        return;
    }

    Hitbox *miHitbox = obtenerHitbox();
    Hitbox *hbObjetivo = objetivo->obtenerHitbox();

    if (!miHitbox || !hbObjetivo)
        return;

    if (miHitbox->colisionaCon(hbObjetivo))
    {
        atacarEntidad(objetivo);
        contadorCuadrosAtaque = cuadrosEntreAtaques;
        qDebug() << "EnemigoSoldadoIA atacó. Vida jugador:" << objetivo->obtenerVida();
    }
}

void EnemigoSoldadoIA::actualizarSprite()
{
    if (contadorDisparoFrames > 0)
    {
        contadorDisparoFrames--;
        if (contadorDisparoFrames <= 0)
            disparando = false;
    }

    bool enElAire = (posicionY < sueloY - 0.1f);

    if (enElAire)
    {
        if (direccion >= 0 && !spriteSaltarDerecha.isNull())
            setPixmap(spriteSaltarDerecha.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        else if (!spriteSaltarIzquierda.isNull())
            setPixmap(spriteSaltarIzquierda.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        return;
    }

    if (disparando)
    {
        if (direccion >= 0 && !spriteDispararDerecha.isNull())
            setPixmap(spriteDispararDerecha.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        else if (!spriteDispararIzquierda.isNull())
            setPixmap(spriteDispararIzquierda.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        return;
    }

    if (velocidadX == 0.0f)
    {
        if (!spriteEstatico.isNull())
            setPixmap(spriteEstatico.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    else if (velocidadX > 0.0f)
    {
        if (!spriteCorrerDerecha.isNull())
            setPixmap(spriteCorrerDerecha.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    else
    {
        if (!spriteCorrerIzquierda.isNull())
            setPixmap(spriteCorrerIzquierda.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}
