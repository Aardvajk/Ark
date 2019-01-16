#ifndef GUIPANEL_H
#define GUIPANEL_H

#include <QPxWidgets/QPxSplitterPanel.h>

namespace QPx
{

class Settings;
class VBoxLayout;

}

class GuiBar;
class QAction;
class QBoxLayout;

class GuiPanel : public QPx::SplitterPanel
{
    Q_OBJECT

public:
    explicit GuiPanel(QWidget *parent = nullptr);

    GuiBar *toolBar() const;
    QAction *closeAction() const;

    QPx::VBoxLayout *layout() const;

    virtual void saveState(QPx::Settings &settings) const = 0;
    virtual void restoreState(const QPx::Settings &settings) = 0;

protected:
    virtual GuiPanel *clone() const = 0;

    virtual QSplitter *createSplitter(Qt::Orientation orientation) const override;

private slots:
    void menuAboutToShow();

    void splitVertical();
    void splitHorizontal();
    void splitGrid();
    void closePanel();

private:
    GuiBar *bar;
    QAction *close;
};

#endif // GUIPANEL_H
