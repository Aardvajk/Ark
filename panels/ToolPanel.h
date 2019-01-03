#ifndef TOOLPANEL_H
#define TOOLPANEL_H

#include <QtWidgets/QWidget>

#include <pcx/aligned_store.h>

class Tool;
class ModelViewRelay;

class ToolPanel : public QWidget
{
    Q_OBJECT

public:
    ToolPanel(ModelViewRelay *relay, QWidget *parent = nullptr);

    Tool *addTool(Tool *tool);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private slots:
    void toggled(bool state);
    void selected();

private:
    pcx::aligned_store<64> cache;
};

#endif // TOOLPANEL_H
