#ifndef GUIPANEL_H
#define GUIPANEL_H

#include <QPxWidgets/QPxSplitterPanel.h>

namespace QPx
{

class Settings;

}

class GuiBar;
class QMenu;
class QAction;

class GuiPanel : public QPx::SplitterPanel
{
    Q_OBJECT

public:
    enum class SplitType
    {
        Vertical,
        Horizontal,
        Both
    };

    explicit GuiPanel(QWidget *parent = nullptr);

    GuiBar *toolBar() const;

    void addSplitButton(SplitType type);

    virtual void saveState(QPx::Settings &settings) const = 0;
    virtual void restoreState(const QPx::Settings &settings) = 0;

protected:
    virtual GuiPanel *clone() const = 0;

    virtual QSplitter *createSplitter(Qt::Orientation orientation) const override;

private slots:
    void menuAboutToShow();

    void splitVertical();
    void splitHorizontal();
    void closePanel();

private:
    GuiBar *bar;
    QMenu *menu;
    QAction *closeAction;
};

#endif // GUIPANEL_H
