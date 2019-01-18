#include "MainWindow.h"

#include "core/Relay.h"

#include "actions/ActionList.h"
#include "actions/ApplicationActions.h"
#include "actions/EditActions.h"
#include "actions/LayoutActions.h"

#include "models/Model.h"

#include "graphics/Graphics.h"

#include "gui/GuiCentralWidget.h"
#include "gui/GuiSplitter.h"
#include "gui/GuiSeparator.h"
#include "gui/GuiBar.h"
#include "gui/GuiContainer.h"

#include "containers/ToolViewContainer.h"
#include "containers/SideViewContainer.h"
#include "containers/ModelViewContainer.h"

#include "properties/PropertyTypeFactory.h"

#include "tools/ToolList.h"
#include "tools/SelectTool.h"
#include "tools/MoveTool.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtCore/QFileInfo>

#include <QtCore/QTimer>

MainWindow::MainWindow(QWidget *parent) : QPx::MainWindow(parent)
{
    actions = new ActionList(settings["Actions"], this);

    auto graphics = new Graphics(this);

    model = new Model(graphics, this);

    auto relay = new Relay(this);
    auto tools = new ToolList(relay, this);
    auto factory = new PropertyTypeFactory(this);

    auto central = setTypedCentralWidget(new GuiCentralWidget());
    central->layout()->addTypedWidget(new GuiSeparator(Qt::Horizontal));

    auto horz = central->layout()->addTypedLayout(new QPx::HBoxLayout(0, 1));

    horz->addTypedWidget(new ToolViewContainer(relay));

    auto split = horz->addTypedWidget(new GuiSplitter(Qt::Horizontal));

    split->addWidget(new SideViewContainer(model, relay, factory), 1);
    split->addWidget(new ModelViewContainer(model, graphics, relay), 16);
    split->addWidget(new SideViewContainer(model, relay, factory), 1);

    horz->addWidget(new ToolViewContainer(relay));

    new ApplicationActions(actions, this);
    new EditActions(model, actions, this);
    new LayoutActions(actions, this);

    tools->addTool(new SelectTool(actions, model, settings["Tools"]["Select"]));
    tools->addTool(new MoveTool(actions, model, settings["Tools"]["Move"]));

    loadInterface("C:/Projects/Ark/Ark/resources/text/mainwindowui.qps", actions);

    restoreGeometry(settings["Application"]["Geometry"].value<QByteArray>());

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

    setWindowTitle(QString("%1%2Ark%3").arg(file).arg(model->path().isEmpty() ? "" : " - ").arg(mod));
}
