#ifndef TOOLPANEL_H
#define TOOLPANEL_H

#include <QtWidgets/QWidget>

class GuiButtonGroup;
class Tool;
class ModelViewRelay;

class ToolPanel : public QWidget
{
    Q_OBJECT

public:
    ToolPanel(ModelViewRelay *relay, QWidget *parent = nullptr);

    Tool *addTool(Tool *tool);
    void addStretch();

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private slots:
    void toggled(bool state);
    void selected();

private:
    ModelViewRelay *relay;
    GuiButtonGroup *group;
    Tool *current;
};

#endif // TOOLPANEL_H
