#ifndef TOOLVIEWCONTAINER_H
#define TOOLVIEWCONTAINER_H

#include "gui/GuiLayoutWidget.h"

class ToolViewContainer : public GuiLayoutWidget
{
    Q_OBJECT

public:
    explicit ToolViewContainer(QWidget *parent = nullptr);
};

#endif // TOOLVIEWCONTAINER_H
