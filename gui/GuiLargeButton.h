#ifndef GUILARGEBUTTON_H
#define GUILARGEBUTTON_H

#include "gui/GuiButton.h"

#include <QtGUi/QIcon>

class GuiLargeButton : public GuiButton
{
    Q_OBJECT

public:
    GuiLargeButton(const QString &text, const QIcon &icon, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // GUILARGEBUTTON_H
