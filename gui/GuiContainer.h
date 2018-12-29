#ifndef GUICONTAINER_H
#define GUICONTAINER_H

#include <QtWidgets/QWidget>

namespace QPx
{

class Settings;

}

class GuiPanel;

class GuiContainer : public QWidget
{
    Q_OBJECT

public:
    explicit GuiContainer(QWidget *parent = nullptr);
    GuiContainer(GuiPanel *panel, QWidget *parent = nullptr);

    void addPanel(GuiPanel *panel);

    void saveState(QPx::Settings &settings) const;
    void restoreState(const QPx::Settings &settings);

public slots:
    void clear();

protected:
    virtual GuiPanel *createPanel() const = 0;

private:
    void saveContainerState(QWidget *widget, QPx::Settings &settings) const;
    QWidget *restoreContainerState(const QPx::Settings &settings);
};

#endif // GUICONTAINER_H
