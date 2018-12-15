#include "MainWindow.h"

#include "actions/ActionList.h"
#include "actions/ApplicationActions.h"

#include "models/Model.h"

#include "graphics/Graphics.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtCore/QFileInfo>

#include <QPxView/QPxViewPanel.h>
#include <QPxView/QPxViewBar.h>
#include <QPxView/QPxViewBarButton.h>
#include <QPxView/QPxViewBarButtonGroup.h>
#include <QPxView/QPxViewSeparator.h>

#include <QtGui/QPainter>
#include <QtWidgets/QColorDialog>

class StandIn : public QWidget
{
public:
    StandIn() : c(Qt::white) { setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); }

    virtual void paintEvent(QPaintEvent *){ QPainter p(this); p.fillRect(rect(), c); }
    virtual void mousePressEvent(QMouseEvent *){ QColorDialog d(c, this); if(d.exec() == QDialog::Accepted){ c = d.currentColor(); update(); } }

    QColor c;
};

class Panel : public QPx::ViewPanel
{
public:
    Panel();

protected:
    virtual Panel *clone() const { return new Panel(); }
};

Panel::Panel()
{
    layout()->addWidget(new StandIn());
}

MainWindow::MainWindow(QWidget *parent) : QPx::MainWindow(parent)
{
    setCentralWidget(new QWidget());
    auto layout = new QPx::VBoxLayout(centralWidget());

    layout->addWidget(new QPx::ViewSeparator(Qt::Horizontal));

    auto horz = new QPx::HBoxLayout();
    layout->addLayout(horz);

    auto p = horz->addTypedWidget(new Panel());

    horz->addWidget(new QPx::ViewSeparator(Qt::Vertical));
    auto panel = horz->addTypedWidget(new QPx::ViewBar(Qt::Vertical, QPx::ViewBar::Type::Large));

    auto group = new QPx::ViewBarButtonGroup(panel);;

    panel->addTypedWidget(group->addButton(new QPx::ViewBarButton("Select", QPixmap(":/resources/images/ark.png"), panel)));
    panel->addTypedWidget(group->addButton(new QPx::ViewBarButton("Move", QPixmap(":/resources/images/ark.png"), panel)));
    panel->addTypedWidget(group->addButton(new QPx::ViewBarButton("Create", QPixmap(":/resources/images/ark.png"), panel)));

    panel->addStretch();
    panel->addSeparator();
    auto ex = panel->addTypedWidget(new QPx::ViewBarButton("Exit", QPixmap(":/resources/images/ark.png"), panel));
    connect(ex, SIGNAL(clicked()), SLOT(close()));

    actions = new ActionList(settings["Actions"], this);
    model = new Model(this);

    new ApplicationActions(actions, this);

    loadInterface("C:/Projects/Ark/Ark/resources/text/mainwindowui.qps", actions);

    restoreGeometry(settings["Application"]["Geometry"].value().toByteArray());

    connect(model, SIGNAL(modifiedStateChanged(bool)), SLOT(updateTitle()));
    connect(model, SIGNAL(pathChanged(QString)), SLOT(updateTitle()));

    auto graphics = new Graphics(this);
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
