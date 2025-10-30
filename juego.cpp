#include "juego.h"
#include "ui_juego.h"

juego::juego(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::juego)
{
    ui->setupUi(this);
}

juego::~juego()
{
    delete ui;
}
