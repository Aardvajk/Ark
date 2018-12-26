#include "GuiBarButtonGroup.h"

#include "gui/GuiBarButton.h"

#include <QtGui/QMouseEvent>

#include <algorithm>

namespace
{

class Cache
{
public:
    QList<GuiBarButton*> buttons;
};

}

GuiBarButtonGroup::GuiBarButtonGroup(QObject *parent) : QObject(parent)
{
    cache.alloc<Cache>();
}

GuiBarButton *GuiBarButtonGroup::addButton(GuiBarButton *button)
{
    cache.get<Cache>().buttons.append(button);
    button->setCheckable(true);

    connect(button, SIGNAL(destroyed(QObject*)), SLOT(buttonDestroyed(QObject*)));
    connect(button, SIGNAL(toggled(bool)), SLOT(buttonToggled(bool)));

    button->installEventFilter(this);

    return button;
}

bool GuiBarButtonGroup::eventFilter(QObject *object, QEvent *event)
{
    if((event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease) && static_cast<QMouseEvent*>(event)->button() == Qt::LeftButton)
    {
        auto button = qobject_cast<GuiBarButton*>(object);

        if(button->isChecked())
        {
            return true;
        }
    }

    return QObject::eventFilter(object, event);
}

void GuiBarButtonGroup::buttonDestroyed(QObject *button)
{
    auto &b = cache.get<Cache>().buttons;
    b.erase(std::remove(b.begin(), b.end(), static_cast<GuiBarButton*>(button)), b.end());
}

void GuiBarButtonGroup::buttonToggled(bool state)
{
    if(state)
    {
        for(auto &button: cache.get<Cache>().buttons)
        {
            if(button != sender())
            {
                button->setChecked(false);
            }
        }
    }
}
