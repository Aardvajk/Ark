#ifndef VIEWPANEL_H
#define VIEWPANEL_H

#include <QPxWidgets/QPxSplitterPanel.h>

namespace QPx
{

class Settings;

}

class QAction;
class ViewBar;

class ViewPanel : public QPx::SplitterPanel
{
    Q_OBJECT

public:
    explicit ViewPanel(QWidget *parent = nullptr);

    ViewBar *viewBar() const;

    virtual void saveState(QPx::Settings &settings) const = 0;

protected:
    virtual ViewPanel *clone() const = 0;

    virtual QSplitter *createSplitter(Qt::Orientation orientation) const override;

private slots:
    void menuAboutToShow();

    void splitVertical();
    void splitHorizontal();
    void closePanel();

private:
    ViewBar *bar;
    QAction *closeAction;
};

#endif // VIEWPANEL_H
