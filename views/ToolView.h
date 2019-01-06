#ifndef TOOLVIEW_H
#define TOOLVIEW_H

#include <QtWidgets/QWidget>

class GuiButtonGroup;

class ToolView : public QWidget
{
    Q_OBJECT

public:
    explicit ToolView(QWidget *parent = nullptr);

private:
    GuiButtonGroup *group;
};

#endif // TOOLVIEW_H
