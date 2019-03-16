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
    gui/GuiPanel.cpp \
    gui/GuiSeparator.cpp \
    gui/GuiContainer.cpp \
    gui/GuiSplitter.cpp \
    models/ModelData.cpp \
    entity/Entity.cpp \
    properties/PropertyMap.cpp \
	core/Mesh.cpp \
    entity/EntityFactory.cpp \
    graphics/buffers/Buffer.cpp \
    graphics/buffers/PreviewBuffer.cpp \
    models/ModelBuffers.cpp \
    graphics/RenderState.cpp \
    graphics/RenderPrimitives.cpp \
    gui/GuiBar.cpp \
    panels/ModelViewPanel.cpp \
    gui/GuiButton.cpp \
    gui/GuiButtonGroup.cpp \
    commands/Command.cpp \
    actions/EditActions.cpp \
    gui/GuiComboBox.cpp \
    core/Relay.cpp \
    containers/ModelViewContainer.cpp \
    views/ToolView.cpp \
    containers/ToolViewContainer.cpp \
    gui/GuiCentralWidget.cpp \
    gui/GuiSmallButton.cpp \
    gui/GuiLargeButton.cpp \
    panels/SideViewPanel.cpp \
    containers/SideViewContainer.cpp \
    options/LayoutOptionsWidget.cpp \
    options/components/LayoutDiagram.cpp \
    actions/LayoutActions.cpp \
    options/KeyboardOptionsWidget.cpp \
    options/OptionsWidget.cpp \
    tools/MoveTool.cpp \
    tools/SelectTool.cpp \
    tools/Tool.cpp \
    tools/ToolList.cpp \
    tools/components/Marquee.cpp \
    core/Element.cpp \
	core/Selection.cpp \
    graphics/buffers/FaceBuffer.cpp \
    graphics/buffers/PointBuffer.cpp \
    gui/GuiTextButton.cpp \
    controls/SettingsCheckBox.cpp \
    views/ToolOptionsView.cpp \
    controls/SettingsElementBox.cpp \
    maths/Intersect.cpp \
    properties/PropertyMapList.cpp \
    commands/ModifyPropertyCommand.cpp \
    views/PropertyView.cpp \
    models/PropertyModel.cpp \
    models/ModelCache.cpp \
    properties/PropertyTypeFactory.cpp \
    properties/types/VecPropertyBrowserType.cpp \
    commands/ModifySelectionCommand.cpp \
    actions/FileActions.cpp \
    maths/Projection.cpp \
    views/modelview/PerspectiveModelView.cpp \
    views/modelview/ModelView.cpp \
    views/modelview/OrthoModelView.cpp \
    graphics/OrthoGrid.cpp \
    core/Render.cpp \
    commands/MoveSelectionCommand.cpp \
    maths/Grid.cpp \
    tools/CreateTool.cpp \
    commands/CreateEntityCommand.cpp \
    commands/CompositeCommand.cpp \
    actions/SelectActions.cpp \
    tools/CursorTool.cpp \
    commands/DeleteEntityCommand.cpp \
    actions/ClipboardActions.cpp \
    commands/CopyEntitiesCommand.cpp \
    actions/ExportActions.cpp \
    export/Export.cpp \
    core/ResourcePath.cpp \
    core/ShaderCompiler.cpp \
    properties/types/TextureDataPropertyBrowserType.cpp

HEADERS += \
        MainWindow.h \
    actions/ActionList.h \
    actions/ApplicationActions.h \
    options/OptionsDialog.h \
    models/Model.h \
    graphics/Graphics.h \ 
    gui/GuiPanel.h \
    gui/GuiSeparator.h \
    gui/GuiContainer.h \
    gui/GuiSplitter.h \
    properties/Property.h \
    models/ModelData.h \
    entity/Entity.h \
    properties/PropertyMap.h \
	core/Mesh.h \
    core/Face.h \
    entity/EntityFactory.h \
    graphics/vertices/ColorVertex.h \
    graphics/vertices/PreviewVertex.h \
    graphics/buffers/Buffer.h \
    graphics/buffers/PreviewBuffer.h \
    graphics/components/EdgeKey.h \
    models/ModelBuffers.h \
    graphics/RenderParams.h \
    graphics/RenderState.h \
    graphics/RenderPrimitives.h \
    gui/GuiBar.h \
    panels/ModelViewPanel.h \
    gui/GuiButton.h \
    gui/GuiButtonGroup.h \
    commands/Command.h \
    actions/EditActions.h \
    gui/GuiComboBox.h \
    core/Relay.h \
    containers/ModelViewContainer.h \
    views/ToolView.h \
    containers/ToolViewContainer.h \
    gui/GuiCentralWidget.h \
    gui/GuiSmallButton.h \
    gui/GuiLargeButton.h \
    panels/SideViewPanel.h \
    containers/SideViewContainer.h \
    options/LayoutOptionsWidget.h \
    options/components/LayoutDiagram.h \
    actions/LayoutActions.h \
    options/KeyboardOptionsWidget.h \
    options/OptionsWidget.h \
    tools/MoveTool.h \
    tools/SelectTool.h \
    tools/Tool.h \
    tools/ToolList.h \
    tools/components/Marquee.h \
	core/Selection.h \
    core/Element.h \
    graphics/buffers/FaceBuffer.h \
    graphics/buffers/PointBuffer.h \
    gui/GuiTextButton.h \
    controls/SettingsCheckBox.h \
    views/ToolOptionsView.h \
    controls/SettingsElementBox.h \
    maths/Intersect.h \
    properties/PropertyMapList.h \
    commands/StoredValue.h \
    commands/ModifyPropertyCommand.h \
    views/PropertyView.h \
    models/PropertyModel.h \
    models/ModelCache.h \
    properties/PropertyTypeFactory.h \
    properties/types/VecPropertyBrowserType.h \
    commands/ModifySelectionCommand.h \
    actions/FileActions.h \
    maths/Projection.h \
    views/modelview/ModelViewState.h \
    views/modelview/PerspectiveModelView.h \
    views/modelview/ModelView.h \
    views/modelview/OrthoModelView.h \
    graphics/OrthoGrid.h \
    core/Render.h \
    commands/MoveSelectionCommand.h \
    maths/Grid.h \
    tools/CreateTool.h \
    commands/CreateEntityCommand.h \
    commands/CompositeCommand.h \
    actions/SelectActions.h \
    tools/CursorTool.h \
    commands/DeleteEntityCommand.h \
    actions/ClipboardActions.h \
    commands/CopyEntitiesCommand.h \
    actions/ExportActions.h \
    export/Export.h \
    core/ResourcePath.h \
    core/ShaderCompiler.h \
    core/TextureData.h \
    properties/types/TextureDataPropertyBrowserType.h

DISTFILES +=

RESOURCES += \
    resources.qrc

RC_FILE += \
   Ark.rc
