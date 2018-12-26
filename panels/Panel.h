#ifndef PANEL_H
#define PANEL_H

#include "gui/GuiPanel.h"

class Panel : public GuiPanel
{
    Q_OBJECT

public:
    explicit Panel(QWidget *parent = nullptr);
};

#endif // PANEL_H
