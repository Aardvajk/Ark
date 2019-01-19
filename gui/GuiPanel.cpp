#include "GuiPanel.h"

#include "gui/GuiSplitter.h"
#include "gui/GuiBar.h"
#include "gui/GuiSmallButton.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtCore/QTimer>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>

namespace
{

bool inParentChain(QWidget *widget, QWidget *parent)
{
    auto p = widget->parentWidget();
    while(p)
    {
        if(p == parent) return true;
        p = p->parentWidget();
    }

    return false;
}

void hideAllExcept(QWidget *parent, QWidget *widget, QVector<QWidget*> &hidden)
{
    for(auto o: parent->children())
    {
        if(auto w = qobject_cast<QWidget*>(o))
        {
            if(qobject_cast<QSplitter*>(w))
            {
                if(!inParentChain(widget, w))
                {
                    hidden.append(w);
                    w->setVisible(false);
                }
                else
                {
                    hideAllExcept(w, widget, hidden);
                }
            }
            else if(w != widget)
            {
                hidden.append(w);
                w->setVisible(false);
            }
        }
    }
}

}

GuiPanel::GuiPanel(QWidget *parent) : QPx::SplitterPanel(parent), btn(nullptr), max(new QAction(QIcon(":/resources/images/splitnone.png"), "Maximize", this)), close(new QAction("Close", this))
{
    auto layout = new QPx::VBoxLayout(0, 1, this);

    bar = layout->addTypedWidget(new GuiBar());

    connect(max, SIGNAL(triggered()), SLOT(maximizePanel()));
    connect(close, SIGNAL(triggered()), SLOT(closePanel()));
}

GuiBar *GuiPanel::toolBar() const
{
    return bar;
}

GuiSmallButton *GuiPanel::button() const
{
    return btn;
}

QAction *GuiPanel::maximizeAction() const
{
    return max;
}

QAction *GuiPanel::closeAction() const
{
    return close;
}

QPx::VBoxLayout *GuiPanel::layout() const
{
    return static_cast<QPx::VBoxLayout*>(QPx::SplitterPanel::layout());
}

GuiSmallButton *GuiPanel::setPanelButton(GuiSmallButton *button)
{
    return btn = button;
}

QSplitter *GuiPanel::createSplitter(Qt::Orientation orientation) const
{
    return new GuiSplitter(orientation);
}

void GuiPanel::menuAboutToShow()
{
    if(auto menu = qobject_cast<QMenu*>(sender()))
    {
        for(auto a: menu->actions())
        {
            if(hidden)
            {
                if(a == max)
                {
                    a->setText("Restore");
                    a->setVisible(true);
                }
                else
                {
                    a->setVisible(false);
                }
            }
            else
            {
                if(a == max)
                {
                    a->setText("Maximize");
                    a->setVisible(qobject_cast<QSplitter*>(parentWidget()));
                }
                else if(a == close)
                {
                    a->setVisible(qobject_cast<QSplitter*>(parentWidget()));
                }
                else
                {
                    a->setVisible(true);
                }
            }
        }
    }
}

void GuiPanel::splitVertical()
{
    split(Qt::Vertical, clone());
}

void GuiPanel::splitHorizontal()
{
    split(Qt::Horizontal, clone());
}

void GuiPanel::splitGrid()
{
    split(Qt::Vertical, clone())->split(Qt::Horizontal, clone());
    split(Qt::Horizontal, clone());
}

void GuiPanel::maximizePanel()
{
    if(hidden)
    {
        for(auto w: *hidden)
        {
            w->setVisible(true);
        }

        hidden = pcx::nullopt;

        if(btn)
        {
            btn->setIcon(max->icon());
            max->setIcon(QIcon(":/resources/images/splitnone.png"));
        }
    }
    else
    {
        auto pw = parentWidget();
        while(qobject_cast<QSplitter*>(pw))
        {
            pw = pw->parentWidget();
        }

        hidden = QVector<QWidget*>();
        hideAllExcept(pw, this, *hidden);

        if(btn)
        {
            max->setIcon(btn->icon());
            btn->setIcon(QIcon(":/resources/images/splitnone.png"));
        }
    }
}

void GuiPanel::closePanel()
{
    QTimer::singleShot(0, this, SLOT(close()));
}
