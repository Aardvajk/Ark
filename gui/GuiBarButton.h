#ifndef GUIBARBUTTON_H
#define GUIBARBUTTON_H

#include "gui/GuiButton.h"

class GuiBarButton : public GuiButton
{
public:
    GuiBarButton(const QPixmap &pixmap, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QPixmap pixmap;
};

#endif // GUIBARBUTTON_H
