#ifndef TOOLVIEW_H
#define TOOLVIEW_H

#include <QtCore/QHash>

#include <QtWidgets/QWidget>

#include <pcx/scoped_lock.h>

class Relay;
class Tool;
class QBoxLayout;
class GuiButton;
class GuiButtonGroup;

class ToolView : public QWidget
{
    Q_OBJECT

public:
    explicit ToolView(Relay *relay, QWidget *parent = nullptr);

private slots:
    void toolAdded(Tool *tool);
    void toolSelected(Tool *tool);

    void buttonToggled(bool state);

private:
    QBoxLayout *layout;
    GuiButtonGroup *group;
    QHash<Tool*, GuiButton*> mapping;

    pcx::lock lock;
};

#endif // TOOLVIEW_H
