#include "GuiButtonGroup.h"

#include "gui/GuiButton.h"

#include <QtGui/QMouseEvent>

#include <algorithm>

namespace
{

class Cache
{
public:
    QList<GuiButton*> buttons;
};

}

GuiButtonGroup::GuiButtonGroup(QObject *parent) : QObject(parent)
{
    cache.alloc<Cache>();
}

GuiButton *GuiButtonGroup::addButton(GuiButton *button)
{
    cache.get<Cache>().buttons.append(button);
    button->setCheckable(true);

    connect(button, SIGNAL(destroyed(QObject*)), SLOT(buttonDestroyed(QObject*)));
    connect(button, SIGNAL(toggled(bool)), SLOT(buttonToggled(bool)));

    button->installEventFilter(this);

    return button;
}

int GuiButtonGroup::count() const
{
    return cache.get<Cache>().buttons.count();
}

bool GuiButtonGroup::eventFilter(QObject *object, QEvent *event)
{
    if((event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease) && static_cast<QMouseEvent*>(event)->button() == Qt::LeftButton)
    {
        auto button = qobject_cast<GuiButton*>(object);

        if(button->isChecked())
        {
            return true;
        }
    }

    return QObject::eventFilter(object, event);
}

void GuiButtonGroup::buttonDestroyed(QObject *button)
{
    auto &b = cache.get<Cache>().buttons;
    b.erase(std::remove(b.begin(), b.end(), static_cast<GuiButton*>(button)), b.end());
}

void GuiButtonGroup::buttonToggled(bool state)
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
