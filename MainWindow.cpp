#include "MainWindow.h"

#include "core/Relay.h"

#include "actions/ActionList.h"
#include "actions/ApplicationActions.h"
#include "actions/FileActions.h"
#include "actions/ExportActions.h"
#include "actions/EditActions.h"
#include "actions/ClipboardActions.h"
#include "actions/SelectActions.h"
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
#include "tools/CreateTool.h"
#include "tools/CursorTool.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtCore/QFileInfo>

#include <QtGui/QCloseEvent>

#include <QtWidgets/QMenu>

MainWindow::MainWindow(QWidget *parent) : QPx::MainWindow(parent)
{
    actions = new ActionList(settings["Actions"], this);

    auto graphics = new Graphics(this);

    model = new Model(graphics, this);

    auto relay = new Relay(this);
    auto tools = new ToolList(relay, this);
    auto factory = new PropertyTypeFactory(model, this);

    auto central = setTypedCentralWidget(new GuiCentralWidget());
    central->layout()->addTypedWidget(new GuiSeparator(GuiSeparator::Style::Line, Qt::Horizontal));

    auto horz = central->layout()->addTypedLayout(new QPx::HBoxLayout(0, 1));

    horz->addTypedWidget(new ToolViewContainer(relay));

    split = horz->addTypedWidget(new GuiSplitter(Qt::Horizontal));

    gcs[0] = split->addTypedWidget(new SideViewContainer(model, relay, factory), 1);
    gcs[1] = split->addTypedWidget(new ModelViewContainer(model, graphics, relay), 16);
    gcs[2] = split->addTypedWidget(new SideViewContainer(model, relay, factory), 1);

    horz->addWidget(new ToolViewContainer(relay));

    new ApplicationActions(actions, this);
    fileActions = new FileActions(model, actions, this);
    new ExportActions(model, actions, this);
    new EditActions(model, actions, this);
    new ClipboardActions(model, actions, this);
    new SelectActions(model, actions, settings["Tools"], this);
    new LayoutActions(actions, this);

    tools->addTool(new SelectTool(actions, model, settings["Tools"]));
    tools->addTool(new MoveTool(actions, model, settings["Tools"]));
    tools->addTool(new CreateTool(actions, model, settings["Tools"]));
    tools->addTool(new CursorTool(actions, model, settings["Tools"]));

    loadInterface(":/resources/text/mainwindowui.qps", actions);

    restoreGeometry(settings["Application"]["Geometry"].value<QByteArray>());
    split->restoreState(settings["Application"]["Splitter"].value<QByteArray>());
    fileActions->setRecentFiles(settings["Application"]["RecentFiles"].value<QStringList>());

    gcs[0]->restoreState(settings["Application"]["Left.Sidebar"]);
    gcs[1]->restoreState(settings["Application"]["Model.View"]);
    gcs[2]->restoreState(settings["Application"]["Right.Sidebar"]);

    connect(model, SIGNAL(modifiedStateChanged(bool)), SLOT(updateTitle()));
    connect(model, SIGNAL(pathChanged(QString)), SLOT(updateTitle()));

    actions->find("Tools.Select")->trigger();

auto recent = fileActions->recentFilesMenu();
if(recent->actions().count() > 1)
{
    recent->actions()[0]->trigger();
}
}

MainWindow::~MainWindow()
{
    delete model;
}

void MainWindow::customInterfaceAction(const QString &key, QWidget *parent)
{
    if(key == "[Recents]")
    {
        static_cast<QMenu*>(parent)->addMenu(fileActions->recentFilesMenu());
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!fileActions->canClose())
    {
        event->ignore();
        return;
    }

    settings["Application"]["Geometry"].setValue(saveGeometry());
    settings["Application"]["Splitter"].setValue(split->saveState());
    settings["Application"]["RecentFiles"].setValue(fileActions->recentFiles());

    gcs[0]->saveState(settings["Application"]["Left.Sidebar"]);
    gcs[1]->saveState(settings["Application"]["Model.View"]);
    gcs[2]->saveState(settings["Application"]["Right.Sidebar"]);

    actions->sync();
    settings.sync();
}

void MainWindow::updateTitle()
{
    QString file = QFileInfo(model->path()).fileName();
    QString mod = model->isModified() ? " (modified)" : "";

    setWindowTitle(QString("%1%2Ark%3").arg(file).arg(model->path().isEmpty() ? "" : " - ").arg(mod));
}
