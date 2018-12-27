#ifndef TOOLPANEL_H
#define TOOLPANEL_H

#include "gui/GuiBar.h"

class Tool;
class GuiBarButton;
class GuiBarButtonGroup;
class ModelViewRelay;

class ToolPanel : public GuiBar
{
    Q_OBJECT

public:
    ToolPanel(ModelViewRelay *relay, QWidget *parent = nullptr);

    Tool *addTool(Tool *tool);

private slots:
    void select();
    void toggle(bool state);

private:
    ModelViewRelay *relay;
    GuiBarButtonGroup *group;
    Tool *current;
    QMap<Tool*, GuiBarButton*> mapping;
};

#endif // TOOLPANEL_H
