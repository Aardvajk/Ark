#ifndef GUISMALLBUTTON_H
#define GUISMALLBUTTON_H

#include "gui/GuiButton.h"

class GuiSmallButton : public GuiButton
{
public:
    GuiSmallButton(const QPixmap &pixmap, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QPixmap pixmap;
};

#endif // GUISMALLBUTTON_H
