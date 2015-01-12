TEMPLATE = app
CONFIG -= console

CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

LIBS += -L/usr/local/lib -lSDL2 -lGLEW -lGL -lGLU

SOURCES += main.cpp \
    models/kvadrat.cpp \
    models/scena1.cpp \
    models/scena2.cpp \
    opengl/cshader.cpp \
    sdl/ltimer.cpp \
    opengl/opengl.cpp \
    opengl/camera.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    models/kvadrat.h \
    models/scena1.h \
    models/scena2.h \
    opengl/cshader.h \
    sdl/ltimer.h \
    opengl/opengl.h \
    opengl/camera.h

DISTFILES += \
    data/shaders/shader.frag \
    data/shaders/shaderm.frag \
    data/shaders/shader.vert \
    data/shaders/shaderm.vert \
    LICENSE


