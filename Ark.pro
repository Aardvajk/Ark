QT += core gui widgets xml

TARGET = Ark
TEMPLATE = app

DEFINES -= UNICODE

QMAKE_CXXFLAGS += -fexceptions -frtti -fno-strict-aliasing \
                  -DQT_NO_CAST_TO_ASCII \
                  -fcheck-new -DNOMINMAX -std=gnu++0x -m64 \
                  -include "QtCore/QDebug"

QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas -Wno-comment -Wno-maybe-uninitialized -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-attributes

QMAKE_LFLAGS += -fexceptions -frtti -fno-builtin -fno-strict-aliasing \
                -static-libgcc -static -Wl,-enable-auto-import \
                -Wl,-enable-runtime-pseudo-reloc -Wl,--as-needed \
                -Wl,-enable-stdcall-fixup -Wl,-allow-multiple-definition -Wl,-enable-auto-import -m64

INCLUDEPATH += "C:/mingw64/x86_64-w64-mingw32.shared/include" \
               "C:/mingw64/x86_64-w64-mingw32.shared/qt5/include" \
               "C:/Projects/pcx" \
               "C:/Projects/Gx/Gx" \
               "C:/Projects/QGx/QGx" \
               "C:/Projects/QPx/QPx"

LIBS += "C:/Projects/QPx/build-QPx/release/libQPx.a" \
        "C:/Projects/pcx/build-pcx/release/libpcx.a"

PRE_TARGETDEPS += "C:/Projects/pcx/build-pcx/release/libpcx.a" \
                  "C:/Projects/QPx/build-QPx/release/libQPx.a"

SOURCES += \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        MainWindow.h
