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
#include "view/ViewContainer.h"

#include <QtGui/QPainter>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QApplication>

class StandIn : public QWidget
{
public:
    explicit StandIn(const QColor &color) : c(color) { setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); }

    virtual void paintEvent(QPaintEvent *){ QPainter p(this); p.fillRect(rect(), c); }
    virtual void mousePressEvent(QMouseEvent *){ QColorDialog d(c, this); if(d.exec() == QDialog::Accepted){ c = d.currentColor(); update(); } }

    QColor c;
};

class Panel : public ViewPanel
{
public:
    explicit Panel(const QColor &color) : s(new StandIn(color)) { layout()->addWidget(s); }
    explicit Panel(const QPx::Settings &settings) : s(new StandIn(qvariant_cast<QColor>(settings["color"].value()))) { layout()->addWidget(s); }

    virtual void saveState(QPx::Settings &settings) const override { settings["color"].setValue(s->c); }

    QColor color() const { return s->c; }

protected:
    virtual Panel *clone() const { return new Panel(color()); }

private:
    StandIn *s;
};

MainWindow::MainWindow(QWidget *parent) : QPx::MainWindow(parent)
{
    setCentralWidget(new QWidget());
    auto layout = new QPx::VBoxLayout(centralWidget());

    layout->addWidget(new ViewSeparator(Qt::Horizontal));

    auto horz = new QPx::HBoxLayout();
    layout->addLayout(horz);

    vc = horz->addTypedWidget(new TypedViewContainer<Panel>());
    vc->addPanel(new Panel(Qt::white));

    horz->addWidget(new ViewSeparator(Qt::Vertical));
    auto panel = horz->addTypedWidget(new ViewBar(Qt::Vertical, ViewBar::Type::Large));

    auto group = new ViewBarButtonGroup(panel);;

    panel->addTypedWidget(group->addButton(new ViewBarButton("Select", QPixmap(":/resources/images/ark.png"), panel)))->setChecked(true);
    panel->addTypedWidget(group->addButton(new ViewBarButton("Move", QPixmap(":/resources/images/ark.png"), panel)));
    panel->addTypedWidget(group->addButton(new ViewBarButton("Create", QPixmap(":/resources/images/ark.png"), panel)));

    panel->addStretch();
    panel->addSeparator();

    connect(panel->addTypedWidget(new ViewBarButton("Clear", QPixmap(":/resources/images/ark.png"), panel)), SIGNAL(clicked()), vc, SLOT(clear()));
    connect(panel->addTypedWidget(new ViewBarButton("Load", QPixmap(":/resources/images/ark.png"), panel)), SIGNAL(clicked()), SLOT(load()));
    connect(panel->addTypedWidget(new ViewBarButton("Save", QPixmap(":/resources/images/ark.png"), panel)), SIGNAL(clicked()), SLOT(save()));

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

void MainWindow::load()
{
    QPx::Settings s;
    s.load("C:/Users/aardv/Desktop/test.txt");

    vc->restoreState(s);
}

void MainWindow::save()
{
    QPx::Settings s;
    vc->saveState(s);

    s.save("C:/Users/aardv/Desktop/test.txt");
}

void MainWindow::updateTitle()
{
    QString file = QFileInfo(model->path()).fileName();
    QString mod = model->isModified() ? " (modified)" : "";

    setWindowTitle(QString("%1%Ark%3").arg(file).arg(model->path().isEmpty() ? "" : " - ").arg(mod));
}
