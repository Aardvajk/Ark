#ifndef GUIPOPUPWINDOW_H
#define GUIPOPUPWINDOW_H

#include <QtWidgets/QFrame>

namespace QPx
{

class UnitAnimation;

}

class GuiPopupWindow : public QFrame
{
    Q_OBJECT

public:
    GuiPopupWindow(QWidget *widget, QWidget *parent = nullptr);

signals:
    void hidden();

public slots:
    void unfold();

protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void hideEvent(QHideEvent *event) override;

private slots:
    void animChanged(float value);

private:
    QWidget *w;
    QSize ss, ts;

    QPx::UnitAnimation *anim;
};

#endif // GUIPOPUPWINDOW_H
