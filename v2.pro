TEMPLATE = app
CONFIG -= console
CONFIG += static
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ./include/mymath/
 win32 {
    #CONFIG += opengl
    LIBS += -L/usr/local/lib -lSDL2 -lGLEW32 -lfreeimage -lfreetype -lopengl32
 }
 !win32 {
    INCLUDEPATH += /usr/include/freetype2/
    LIBS += -L/usr/local/lib -lSDL2 -lGLEW -lGL -lfreeimage -lfreetype
 }
SOURCES += main.cpp \
    models/kvadrat.cpp \
    models/scena1.cpp \
    models/scena2.cpp \
    opengl/cshader.cpp \
    sdl/ltimer.cpp \
    opengl/opengl.cpp \
    opengl/camera.cpp \
    sdl/nksdl.cpp \
    models/scenaindex.cpp \
    opengl/texture.cpp \
    opengl/vertexBufferObject.cpp \
    models/scenatex.cpp \
    models/nkkocka.cpp \
    opengl/shader.cpp \
    opengl/nkgltext.cpp \
    opengl/shader_utils.cpp \
    models/nktut1.cpp \
    models/nkhex.cpp \
    models/nkhex2.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    models/kvadrat.h \
    models/scena1.h \
    models/scena2.h \
    opengl/cshader.h \
    sdl/ltimer.h \
    opengl/opengl.h \
    opengl/camera.h \
    sdl/nksdl.h \
    models/scenaindex.h \
    opengl/texture.h \
    opengl/vertexBufferObject.h \
    models/scenatex.h \
    models/nkkocka.h \
    opengl/shader.hpp \
    opengl/nkgltext.h \
    opengl/shader_utils.h \
    models/nkmodel.h \
    models/nktut1.h \
    models/nkhex.h \
    opengl/framework.h \
    include/mymath/mm_camera.h \
    include/mymath/mm_common.h \
    include/mymath/mm_frame.h \
    include/mymath/mm_mat_func.h \
    include/mymath/mm_mat2_impl.h \
    include/mymath/mm_mat3_impl.h \
    include/mymath/mm_mat4_impl.h \
    include/mymath/mm_matrix_stack.h \
    include/mymath/mm_pipeline.h \
    include/mymath/mm_util.h \
    include/mymath/mm_vec_func.h \
    include/mymath/mm_vec_swizzle_out.h \
    include/mymath/mm_vec2_impl.h \
    include/mymath/mm_vec3_impl.h \
    include/mymath/mm_vec4_impl.h \
    include/mymath/mymath.h \
    include/mymath/includes/vec2_swizzle_declarations.h \
    include/mymath/includes/vec3_swizzle_declarations.h \
    include/mymath/includes/vec4_swizzle_declarations.h \
    models/nkhex2.h

DISTFILES += \
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
    README.md


