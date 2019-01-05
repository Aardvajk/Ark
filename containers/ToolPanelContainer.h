#ifndef TOOLPANELCONTAINER_H
#define TOOLPANELCONTAINER_H

#include <QtWidgets/QWidget>

class ToolPanel;

class ToolPanelContainer : public QWidget
{
    Q_OBJECT

public:
    ToolPanelContainer(ToolPanel *panel, QWidget *parent = 0);
};

#endif // TOOLPANELCONTAINER_H
