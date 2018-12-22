#include "ViewContainer.h"

#include "view/ViewPanel.h"

#include <QPxCore/QPxSettings.h>

#include <QPxWidgets/QPxLayouts.h>
#include <QPxWidgets/QPxLineSplitter.h>
#include <QPxWidgets/QPxPalette.h>

#include <QtWidgets/QApplication>

namespace
{


}

ViewContainer::ViewContainer(ViewPanel *panel, QWidget *parent) : QWidget(parent)
{
    new QPx::VBoxLayout(this);
    layout()->addWidget(panel);
}

void ViewContainer::clear()
{
    auto item = layout()->takeAt(0);

    delete item->widget();
    delete item;
}

void ViewContainer::saveState(QPx::Settings &settings) const
{
    saveContainerState(layout()->itemAt(0)->widget(), settings);
}

void ViewContainer::restoreState(const QPx::Settings &settings)
{
    clear();
    layout()->addWidget(restoreContainerState(settings[0]));
}

void ViewContainer::saveContainerState(QWidget *widget, QPx::Settings &settings) const
{
    if(auto splitter = qobject_cast<const QSplitter*>(widget))
    {
        auto &s = settings.append("splitter");
        s["properties"]["state"].setValue(splitter->saveState());

        saveContainerState(splitter->widget(0), s["first"]);
        saveContainerState(splitter->widget(1), s["second"]);
    }
    else if(auto panel = qobject_cast<const ViewPanel*>(widget))
    {
        panel->saveState(settings.append("panel"));
    }
}

QWidget *ViewContainer::restoreContainerState(const QPx::Settings &settings)
{
    if(settings.key() == "splitter")
    {
        auto &p = settings["properties"];

        auto splitter = new QPx::LineSplitter(Qt::Vertical);
        QPx::setPaletteColor(splitter, QPalette::Background, qvariant_cast<QColor>(QApplication::instance()->property("ui-border")));

        splitter->addWidget(restoreContainerState(settings["first"][0]));
        splitter->addWidget(restoreContainerState(settings["second"][0]));

        splitter->restoreState(p["state"].value().toByteArray());

        return splitter;
    }
    else
    {
        return createPanel(settings);
    }
}
