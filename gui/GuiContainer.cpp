#include "GuiContainer.h"

#include "gui/GuiPanel.h"
#include "gui/GuiSplitter.h"

#include <QPxCore/QPxSettings.h>

#include <QPxWidgets/QPxLayouts.h>
#include <QPxWidgets/QPxLineSplitter.h>

#include <QtWidgets/QApplication>

GuiContainer::GuiContainer(QWidget *parent) : QWidget(parent)
{
    new QPx::VBoxLayout(this);
}

GuiContainer::GuiContainer(GuiPanel *panel, QWidget *parent) : QWidget(parent)
{
    new QPx::VBoxLayout(this);
    layout()->addWidget(panel);
}

void GuiContainer::addPanel(GuiPanel *panel)
{
    layout()->addWidget(panel);
}

void GuiContainer::saveState(QPx::Settings &settings) const
{
    saveContainerState(layout()->itemAt(0)->widget(), settings);
}

void GuiContainer::restoreState(const QPx::Settings &settings)
{
    clear();
    layout()->addWidget(restoreContainerState(settings[0]));
}

void GuiContainer::clear()
{
    if(layout()->count())
    {
        auto item = layout()->takeAt(0);

        delete item->widget();
        delete item;
    }
}

void GuiContainer::saveContainerState(QWidget *widget, QPx::Settings &settings) const
{
    if(auto splitter = qobject_cast<const QSplitter*>(widget))
    {
        auto &s = settings.append("splitter");
        s.setValue(splitter->saveState());

        saveContainerState(splitter->widget(0), s);
        saveContainerState(splitter->widget(1), s);
    }
    else if(auto panel = qobject_cast<const GuiPanel*>(widget))
    {
        panel->saveState(settings.append("panel"));
    }
}

QWidget *GuiContainer::restoreContainerState(const QPx::Settings &settings)
{
    if(settings.key() == "splitter")
    {
        auto splitter = new GuiSplitter(Qt::Vertical);

        splitter->addWidget(restoreContainerState(settings[0]));
        splitter->addWidget(restoreContainerState(settings[1]));

        splitter->restoreState(settings.value().toByteArray());

        return splitter;
    }
    else
    {
        auto panel = createPanel();
        panel->restoreState(settings);

        return panel;
    }
}
