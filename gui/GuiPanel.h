#ifndef GUIPANEL_H
#define GUIPANEL_H

#include <QPxWidgets/QPxSplitterPanel.h>

#include <QtGui/QIcon>

#include <pcx/optional.h>

namespace QPx
{

class Settings;
class VBoxLayout;

}

class GuiBar;
class GuiSmallButton;
class QAction;
class QBoxLayout;

class GuiPanel : public QPx::SplitterPanel
{
    Q_OBJECT

public:
    explicit GuiPanel(QWidget *parent = nullptr);

    GuiBar *toolBar() const;
    GuiSmallButton *button() const;

    QAction *maximizeAction() const;
    QAction *closeAction() const;

    QPx::VBoxLayout *layout() const;

    GuiSmallButton *setPanelButton(GuiSmallButton *button);

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
    void maximizePanel();
    void closePanel();

private:
    GuiBar *bar;
    GuiSmallButton *btn;

    QAction *max;
    QAction *close;

    pcx::optional<QVector<QWidget*> > hidden;
};

#endif // GUIPANEL_H
