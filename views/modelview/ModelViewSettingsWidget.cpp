#include "ModelViewSettingsWidget.h"

#include "core/Render.h"

#include "views/modelview/ModelView.h"

#include <QPxWidgets/QPxLayouts.h>
#include <QtWidgets/QComboBox>

#include <pcx/enum_range.h>

ModelViewSettingsWidget::ModelViewSettingsWidget(ModelView *view, QWidget *parent) : QFrame(parent), view(view)
{
    setFrameStyle(QFrame::StyledPanel);

    auto state = view->state();

    auto form = new QPx::FormLayout({ }, { }, this);

    auto rc = form->addTypedRow("Render:", new QComboBox());
    for(auto r: pcx::enum_range(Render::Type::Wireframe, Render::Type::None))
    {
        rc->addItem(Render::toString(r), QVariant::fromValue(r));
        if(r == state.render)
        {
            rc->setCurrentIndex(static_cast<int>(r));
        }
    }

    connect(rc, SIGNAL(currentIndexChanged(int)), SLOT(renderChanged(int)));
}

void ModelViewSettingsWidget::renderChanged(int index)
{
    auto s = view->state();
    s.render = static_cast<QComboBox*>(sender())->itemData(index).value<Render::Type>();

    view->setState(s);
}
