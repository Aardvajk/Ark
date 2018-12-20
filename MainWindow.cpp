#include "MainWindow.h"

#include "actions/ActionList.h"
#include "actions/ApplicationActions.h"

#include "models/Model.h"

#include "graphics/Graphics.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtCore/QFileInfo>

#include "view/ViewPanel.h"
#include "view/ViewBar.h"
#include "view/ViewBarButton.h"
#include "view/ViewBarButtonGroup.h"
#include "view/ViewSeparator.h"

#include <QPxWidgets/QPxSplitterContainer.h>

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

class Panel : public ViewPanel
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

    layout->addWidget(new ViewSeparator(Qt::Horizontal));

    auto horz = new QPx::HBoxLayout();
    layout->addLayout(horz);

    horz->addWidget(new QPx::SplitterContainer(new Panel()));

    horz->addWidget(new ViewSeparator(Qt::Vertical));
    auto panel = horz->addTypedWidget(new ViewBar(Qt::Vertical, ViewBar::Type::Large));

    auto group = new ViewBarButtonGroup(panel);;

    panel->addTypedWidget(group->addButton(new ViewBarButton("Select", QPixmap(":/resources/images/ark.png"), panel)))->setChecked(true);
    panel->addTypedWidget(group->addButton(new ViewBarButton("Move", QPixmap(":/resources/images/ark.png"), panel)));
    panel->addTypedWidget(group->addButton(new ViewBarButton("Create", QPixmap(":/resources/images/ark.png"), panel)));

    panel->addStretch();
    panel->addSeparator();
    auto ex = panel->addTypedWidget(new ViewBarButton("Exit", QPixmap(":/resources/images/ark.png"), panel));
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
