QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000     # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    # Archivos compartidos y tuyos
    main.cpp \
    juego.cpp \
    avionenemigo.cpp \
    nivel2.cpp \
    proyectil.cpp \
    spritesnivel1.cpp \
    # Archivos nuevos de tu compañero (Master)
    enemigo.cpp \
    enemigosoldadoia.cpp \
    entidad.cpp \
    hitbox.cpp \
    nivel.cpp \
    nivel1.cpp \
    nivel3.cpp \
    obstaculo.cpp \
    personajejugador.cpp \
    proyectiln3.cpp \
    soldado.cpp

HEADERS += \
    # Archivos compartidos y tuyos
    juego.h \
    Explosion.h \
    avionenemigo.h \
    nivel2.h \
    proyectil.h \
    spritesnivel1.h \
    # Archivos nuevos de tu compañero (Master)
    enemigo.h \
    enemigosoldadoia.h \
    entidad.h \
    hitbox.h \
    nivel.h \
    nivel1.h \
    nivel3.h \
    obstaculo.h \
    personajejugador.h \
    proyectiln3.h \
    soldado.h

FORMS += \
    juego.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Sprites.qrc \
    esplocion2.qrc \
    esplocionbalas.qrc \
    fondo.qrc \
    splocion1.qrc \
    spriteavionata.qrc \
    spriteavionnormal.qrc \
    spritetan.qrc \
    spritetanqueataca.qrc

DISTFILES += \
    spritetanque atacando/tanquesprite.png \
    spritetanque atacando/tanquesprite.png
