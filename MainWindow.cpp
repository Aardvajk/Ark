#include "MainWindow.h"

#include "actions/ActionList.h"
#include "actions/ApplicationActions.h"

#include "models/Model.h"
#include "models/ModelBuffers.h"

#include "graphics/Graphics.h"

#include "gui/GuiSplitter.h"
#include "gui/GuiSeparator.h"
#include "gui/GuiBar.h"
#include "gui/GuiContainer.h"

#include "panels/ToolPanel.h"
#include "panels/ToolOptionsPanel.h"

#include "containers/PropertyViewContainer.h"
#include "containers/ModelViewContainer.h"

#include "views/ModelViewRelay.h"

#include "tools/SelectTool.h"
#include "tools/MoveTool.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtCore/QFileInfo>

MainWindow::MainWindow(QWidget *parent) : QPx::MainWindow(parent)
{
    setCentralWidget(new QWidget());
    auto layout = new QPx::VBoxLayout(centralWidget());

    actions = new ActionList(settings["Actions"], this);

    auto graphics = new Graphics(this);
    auto relay = new ModelViewRelay(this);

    model = new Model(graphics, this);

    new ApplicationActions(actions, this);

    loadInterface("C:/Projects/Ark/Ark/resources/text/mainwindowui.qps", actions);

    layout->addWidget(new GuiSeparator(Qt::Horizontal));

    auto horz = layout->addTypedLayout(new QPx::HBoxLayout());
    auto vert = horz->addTypedLayout(new QPx::VBoxLayout());

    vert->addTypedWidget(new GuiBar())->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    vert->addTypedWidget(new GuiSeparator(Qt::Horizontal))->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    auto tools = vert->addTypedWidget(new ToolPanel(relay));

    horz->addWidget(new GuiSeparator(Qt::Vertical));

    splitters.append(horz->addTypedWidget(new GuiSplitter(Qt::Horizontal)));
    splitters.append(new GuiSplitter(Qt::Vertical));

//    splitters[1]->addWidget(new TypedGuiContainer<ToolOptionsPanel>(new ToolOptionsPanel()));
    splitters[1]->addWidget(new PropertyViewContainer());

    splitters[0]->addWidget(splitters[1]);
    splitters[0]->addWidget(new ModelViewContainer(model, graphics, relay));

    tools->addTool(new SelectTool(model, actions, this));
    tools->addTool(new MoveTool(model, actions, this));
    tools->addStretch();

    restoreGeometry(settings["Application"]["Geometry"].value().toByteArray());

    connect(model, SIGNAL(modifiedStateChanged(bool)), SLOT(updateTitle()));
    connect(model, SIGNAL(pathChanged(QString)), SLOT(updateTitle()));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    settings["Application"]["Geometry"].setValue(saveGeometry());

    actions->sync();
    settings.sync();
}

void MainWindow::updateTitle()
{
    QString file = QFileInfo(model->path()).fileName();
    QString mod = model->isModified() ? " (modified)" : "";

    setWindowTitle(QString("%1%Ark%3").arg(file).arg(model->path().isEmpty() ? "" : " - ").arg(mod));
}
