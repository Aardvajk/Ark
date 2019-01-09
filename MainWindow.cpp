#include "MainWindow.h"

#include "core/Relay.h"

#include "actions/ActionList.h"
#include "actions/ApplicationActions.h"
#include "actions/EditActions.h"

#include "models/Model.h"
#include "models/ModelBuffers.h"

#include "graphics/Graphics.h"

#include "gui/GuiCentralWidget.h"
#include "gui/GuiSplitter.h"
#include "gui/GuiSeparator.h"
#include "gui/GuiBar.h"
#include "gui/GuiContainer.h"

#include "containers/ToolViewContainer.h"
#include "containers/SideViewContainer.h"
#include "containers/ModelViewContainer.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtCore/QFileInfo>

#include <QtCore/QTimer>

MainWindow::MainWindow(QWidget *parent) : QPx::MainWindow(parent)
{
    actions = new ActionList(settings["Actions"], this);

    auto graphics = new Graphics(this);
    auto relay = new Relay(this);

    model = new Model(graphics, this);

    auto central = setTypedCentralWidget(new GuiCentralWidget());
    central->layout()->addTypedWidget(new GuiSeparator(Qt::Horizontal));

    auto horz = central->layout()->addTypedLayout(new QPx::HBoxLayout(0, 1));
    horz->addWidget(new ToolViewContainer());

    auto split = horz->addTypedWidget(new GuiSplitter(Qt::Horizontal));

    split->addWidget(new SideViewContainer(), 1);
    split->addWidget(new ModelViewContainer(model, graphics, relay), 100);
    split->addWidget(new SideViewContainer(), 1);

    new ApplicationActions(actions, this);
    new EditActions(model, actions, this);

    loadInterface("C:/Projects/Ark/Ark/resources/text/mainwindowui.qps", actions);

    restoreGeometry(settings["Application"]["Geometry"].value().toByteArray());

    connect(model, SIGNAL(modifiedStateChanged(bool)), SLOT(updateTitle()));
    connect(model, SIGNAL(pathChanged(QString)), SLOT(updateTitle()));

    QTimer::singleShot(10, actions->find("Application.Options"), SLOT(trigger()));
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
