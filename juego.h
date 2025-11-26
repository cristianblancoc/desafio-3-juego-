#ifndef JUEGO_H
#define JUEGO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class juego;
}
QT_END_NAMESPACE

class juego : public QMainWindow
{
    Q_OBJECT


public:
    juego(QWidget *parent = nullptr);
    ~juego();

private:
    Ui::juego *ui;
};
#endif // JUEGO_H
