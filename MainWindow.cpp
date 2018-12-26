#include "MainWindow.h"

#include "actions/ActionList.h"
#include "actions/ApplicationActions.h"

#include "models/Model.h"

#include "graphics/Graphics.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtCore/QFileInfo>

#include "views/ModelView.h"

MainWindow::MainWindow(QWidget *parent) : QPx::MainWindow(parent)
{
    setCentralWidget(new QWidget());
    auto layout = new QPx::VBoxLayout(centralWidget());

    actions = new ActionList(settings["Actions"], this);
    model = new Model(this);
    auto graphics = new Graphics(this);

    new ApplicationActions(actions, this);

    loadInterface("C:/Projects/Ark/Ark/resources/text/mainwindowui.qps", actions);

    auto view = layout->addTypedWidget(new ModelView(model, graphics));
    connect(graphics, SIGNAL(render()), view, SLOT(update()));

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
