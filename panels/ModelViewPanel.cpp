#include "ModelViewPanel.h"

#include "core/Relay.h"

#include "maths/Projection.h"

#include "views/modelview/PerspectiveModelView.h"
#include "views/modelview/OrthoModelView.h"
#include "views/modelview/ModelViewSettingsWidget.h"

#include "gui/GuiBar.h"
#include "gui/GuiComboBox.h"
#include "gui/GuiSmallButton.h"
#include "gui/GuiPopupWindow.h"

#include "graphics/Graphics.h"

#include <QtWidgets/QLayout>
#include <QtWidgets/QMenu>

#include <QPxCore/QPxSettings.h>

#include <QPxWidgets/QPxPalette.h>
#include <QPxWidgets/QPxLayouts.h>

#include <pcx/enum_range.h>

ModelViewPanel::ModelViewPanel(Model *model, Graphics *graphics, Relay *relay, QWidget *parent) : GuiPanel(parent), model(model), graphics(graphics), view(nullptr), relay(relay)
{
    connect(toolBar()->addTypedWidget(new GuiSmallButton(QIcon(":/resources/images/ark.png"))), SIGNAL(pressed()), SLOT(settingsPressed()));

    combo = toolBar()->addTypedWidget(new GuiComboBox());
    for(auto p: pcx::enum_range(Projection::Type::Perspective, Projection::Type::None))
    {
        combo->addItem(Projection::toString(p), QVariant::fromValue(p));

        states[p].projection = p;
        states[p].render = p == Projection::Type::Perspective ? Render::Type::Flat : Render::Type::Wireframe;

        states[p].camera = Projection::camera(p);
    }

    connect(combo, SIGNAL(currentIndexChanged(int)), SLOT(comboChanged(int)));

    auto menu = new QMenu(this);

    menu->addAction(QIcon(":/resources/images/splitvert.png"), "Split Vertical", this, SLOT(splitVertical()));
    menu->addAction(QIcon(":/resources/images/splithorz.png"), "Split Horizontal", this, SLOT(splitHorizontal()));
    menu->addAction(QIcon(":/resources/images/splitgrid.png"), "Split Grid", this, SLOT(splitGrid()));
    menu->addSeparator();
    menu->addAction(maximizeAction());
    menu->addAction(closeAction());

    connect(menu, SIGNAL(aboutToShow()), SLOT(menuAboutToShow()));

    auto button = setPanelButton(toolBar()->addTypedWidget(new GuiSmallButton(QIcon(":/resources/images/splitgrid.png"))));
    button->setMenu(menu);

    comboChanged(0);
}

void ModelViewPanel::saveState(QPx::Settings &settings) const
{
    settings["index"].setValue(combo->currentIndex());
}

void ModelViewPanel::restoreState(const QPx::Settings &settings)
{
    combo->setCurrentIndex(settings["index"].value<int>());
}

ModelViewPanel *ModelViewPanel::clone() const
{
    return new ModelViewPanel(model, graphics, relay);
}

void ModelViewPanel::settingsPressed()
{
    if(auto b = qobject_cast<GuiButton*>(sender()))
    {
        auto w = new GuiPopupWindow(new ModelViewSettingsWidget(view), this);
        w->setAttribute(Qt::WA_DeleteOnClose);

        connect(w, SIGNAL(hidden()), b, SLOT(reset()));

        w->fadeIn(b);
    }
}

void ModelViewPanel::comboChanged(int index)
{
    if(view)
    {
        auto s = view->state();
        states[s.projection] = s;

        delete view;
    }

    auto state = states[combo->itemData(index).value<Projection::Type>()];
    switch(state.projection)
    {
        case Projection::Type::Perspective: view = layout()->addTypedWidget(new PerspectiveModelView(model, graphics, state)); break;

        default: view = layout()->addTypedWidget(new OrthoModelView(model, graphics, state));
    }

    connect(view, SIGNAL(mousePressed(ModelView*,QMouseEvent*)), relay, SIGNAL(mousePressed(ModelView*,QMouseEvent*)));
    connect(view, SIGNAL(mouseMoved(ModelView*,QMouseEvent*)), relay, SIGNAL(mouseMoved(ModelView*,QMouseEvent*)));
    connect(view, SIGNAL(mouseReleased(ModelView*,QMouseEvent*)), relay, SIGNAL(mouseReleased(ModelView*,QMouseEvent*)));
    connect(view, SIGNAL(render(ModelView*,Graphics*,RenderParams)), relay, SIGNAL(render(ModelView*,Graphics*,RenderParams)));

    connect(graphics, SIGNAL(render()), view, SLOT(update()));
}
