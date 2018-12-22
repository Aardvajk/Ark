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

ViewContainer::ViewContainer(QWidget *parent) : QWidget(parent)
{
    new QPx::VBoxLayout(this);
}

void ViewContainer::addPanel(ViewPanel *panel)
{
    layout()->addWidget(panel);
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

void ViewContainer::clear()
{
    if(layout()->count())
    {
        auto item = layout()->takeAt(0);

        delete item->widget();
        delete item;
    }
}

void ViewContainer::saveContainerState(QWidget *widget, QPx::Settings &settings) const
{
    if(auto splitter = qobject_cast<const QSplitter*>(widget))
    {
        auto &s = settings.append("splitter");
        s.setValue(splitter->saveState());

        saveContainerState(splitter->widget(0), s);
        saveContainerState(splitter->widget(1), s);
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
        auto splitter = new QPx::LineSplitter(Qt::Vertical);
        QPx::setPaletteColor(splitter, QPalette::Background, qvariant_cast<QColor>(QApplication::instance()->property("ui-border")));

        splitter->addWidget(restoreContainerState(settings[0]));
        splitter->addWidget(restoreContainerState(settings[1]));

        splitter->restoreState(settings.value().toByteArray());

        return splitter;
    }
    else
    {
        return createPanel(settings);
    }
}
