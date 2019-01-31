#ifndef GUIPOPUPWINDOW_H
#define GUIPOPUPWINDOW_H

#include <QtWidgets/QWidget>

namespace QPx
{

class UnitAnimation;

}

class GuiPopupWindow : public QWidget
{
    Q_OBJECT

public:
    GuiPopupWindow(QWidget *widget, QWidget *parent = nullptr);

signals:
    void hidden();

public slots:
    void fadeIn(QWidget *widget);

protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void hideEvent(QHideEvent *event) override;

private slots:
    void animChanged(float value);

private:
    QWidget *w;
    QPx::UnitAnimation *anim;
};

#endif // GUIPOPUPWINDOW_H
