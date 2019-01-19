#ifndef GUISMALLBUTTON_H
#define GUISMALLBUTTON_H

#include "gui/GuiButton.h"

#include <QtGui/QIcon>

class GuiSmallButton : public GuiButton
{
public:
    GuiSmallButton(const QIcon &icon, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QIcon image;
};

#endif // GUISMALLBUTTON_H
