#include <QApplication>
#include "juego.h"
#include "Nivel1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    juego ventana;

    // Cargamos el primer nivel correctamente
    ventana.establecerNivel(new Nivel1(&ventana));
    ventana.iniciarJuego();

    ventana.show();
    return a.exec();
}
