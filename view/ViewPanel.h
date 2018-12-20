#ifndef VIEWPANEL_H
#define VIEWPANEL_H

#include <QPxWidgets/QPxSplitterPanel.h>

class ViewBar;

class ViewPanel : public QPx::SplitterPanel
{
    Q_OBJECT

public:
    explicit ViewPanel(QWidget *parent = nullptr);

    ViewBar *viewBar() const;

protected:
    virtual ViewPanel *clone() const = 0;

private slots:
    void splitVertical();
    void splitHorizontal();
    void closePanel();

    void click();

private:
    ViewBar *bar;

    QVector<QWidget*> ws;
};

#endif // VIEWPANEL_H
