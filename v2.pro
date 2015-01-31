TEMPLATE = app
CONFIG -= console
CONFIG += static
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ./src/
 win32 {
    #CONFIG += opengl
    LIBS += -L/usr/local/lib -lSDL2 -lGLEW32 -lfreeimage -lfreetype -lopengl32
 }
 !win32 {
    INCLUDEPATH += /usr/include/freetype2/
    LIBS += -L/usr/local/lib -lSDL2 -lGLEW -lGL -lfreeimage -lfreetype
 }
include(src/include.pri)


OTHER_FILES += \
    data/shaders/shader.frag \
    data/shaders/shaderm.frag \
    data/shaders/shader.vert \
    data/shaders/shaderm.vert \
    LICENSE \
    data/shaders/shaderindex.frag \
    data/shaders/shaderindex.vert \
    data/shaders/shadertex.frag \
    data/shaders/shadertex.vert \
    data/textures/snow.jpg \
    data/textures/golddiag.jpg \
    data/shaders/TransformVertexShader.vertexshader \
    data/shaders/ColorFragmentShader.fragmentshader \
    data/shaders/text.f.glsl \
    data/shaders/text.v.glsl \
    data/font/FreeSans.ttf \
    README.md \
    doc/potsetnik.org


