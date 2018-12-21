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
        "C:/Projects/pcx/build-pcx/release/libpcx.a" \
        "C:/Projects/Gx/build-Gx/release/libGx.a" \
        "C:/Projects/QGx/build-QGx/release/libQGx.a" \
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/d3d9.lib" \
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/d3dx9.lib" \
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/dxerr.lib" \
        "C:/mingw64/x86_64-w64-mingw32.shared/lib/libuser32.a" \
        "C:/mingw64/x86_64-w64-mingw32.shared/lib/libgdi32.a" \
        "C:/mingw64/x86_64-w64-mingw32.shared/lib/libpsapi.a"

PRE_TARGETDEPS += "C:/Projects/pcx/build-pcx/release/libpcx.a" \
                  "C:/Projects/QPx/build-QPx/release/libQPx.a" \
                  "C:/Projects/Gx/build-Gx/release/libGx.a" \
                  "C:/Projects/QGx/build-QGx/release/libQGx.a"

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    actions/ActionList.cpp \
    actions/ApplicationActions.cpp \
    options/OptionsDialog.cpp \
    models/Model.cpp \
    graphics/Graphics.cpp \ 
    view/ViewBar.cpp \
    view/ViewBarButton.cpp \
    view/ViewBarButtonGroup.cpp \
    view/ViewPanel.cpp \
    view/ViewSeparator.cpp \
    view/ViewContainer.cpp

HEADERS += \
        MainWindow.h \
    actions/ActionList.h \
    actions/ApplicationActions.h \
    options/OptionsDialog.h \
    models/Model.h \
    graphics/Graphics.h \ 
    view/ViewBar.h \
    view/ViewBarButton.h \
    view/ViewBarButtonGroup.h \
    view/ViewPanel.h \
    view/ViewSeparator.h \
    view/ViewContainer.h \
    view/ViewPanelFactory.h

DISTFILES += \
    resources/text/mainwindowui.qps

RESOURCES += \
    resources.qrc

RC_FILE += \
   Ark.rc
