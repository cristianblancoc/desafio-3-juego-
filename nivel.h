#ifndef NIVEL_H
#define NIVEL_H

#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsTextItem>

class QKeyEvent;
class Entidad;

class Nivel : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Nivel(int numeroNivel, QObject *parent = nullptr);
    virtual ~Nivel();

    virtual void iniciarNivel() = 0;
    virtual void actualizarFrame() = 0;
    virtual void procesarTeclaPresionada(QKeyEvent *eventoTecla) = 0;
    virtual void procesarTeclaLiberada(QKeyEvent *eventoTecla) = 0;

    void iniciarTemporizador();
    void detenerTemporizador();

    void prepararCuentaRegresiva(int segundos);
    void actualizarCuentaRegresiva();

    bool estaEnCombate() const;
    int obtenerNumeroNivel() const;

    void marcarVictoria();
    void marcarDerrota();

signals:
    void nivelGanado(int numeroNivel);
    void nivelPerdido(int numeroNivel);

protected:
    void keyPressEvent(QKeyEvent *eventoTecla) override;
    void keyReleaseEvent(QKeyEvent *eventoTecla) override;

    void limitarEntidadEnX(Entidad *entidad, float anchoSprite);

protected slots:
    void onActualizarFrame();

protected:
    int numeroNivel;
    QTimer *temporizador;
    int milisegundosPorFrame;
    bool enCombate;

    QGraphicsTextItem *textoCuentaRegresiva;
    int segundosRestantes;
    int contadorFramesCuenta;
    int framesPorSegundo;

    QGraphicsTextItem *textoResultado;
    bool resultadoMostrado;
};

#endif // NIVEL_H
