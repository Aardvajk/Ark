#include "MainWindow.h"

#include "core/Relay.h"

#include "actions/ActionList.h"
#include "actions/ApplicationActions.h"
#include "actions/EditActions.h"

#include "models/Model.h"
#include "models/ModelBuffers.h"

#include "graphics/Graphics.h"

#include "gui/GuiLayoutWidget.h"
#include "gui/GuiSplitter.h"
#include "gui/GuiSeparator.h"
#include "gui/GuiBar.h"
#include "gui/GuiContainer.h"

#include "containers/ModelViewContainer.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtCore/QFileInfo>

MainWindow::MainWindow(QWidget *parent) : QPx::MainWindow(parent)
{
    actions = new ActionList(settings["Actions"], this);

    auto graphics = new Graphics(this);
    auto relay = new Relay(this);

    model = new Model(graphics, this);

    auto layout = new QPx::VBoxLayout(5, 5);
    setCentralWidget(new GuiLayoutWidget(layout));

    auto splitter = layout->addTypedWidget(new QPx::Splitter(Qt::Horizontal));
    splitter->addWidget(new ModelViewContainer(model, graphics, relay), 20);
    splitter->addWidget(new ModelViewContainer(model, graphics, relay), 20);

    new ApplicationActions(actions, this);
    new EditActions(model, actions, this);

    loadInterface("C:/Projects/Ark/Ark/resources/text/mainwindowui.qps", actions);

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
