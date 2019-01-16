#ifndef GUITEXTBUTTON_H
#define GUITEXTBUTTON_H

#include "gui/GuiButton.h"

class GuiTextButton : public GuiButton
{
    Q_OBJECT

public:
    GuiTextButton(const QString &text, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QString text;
};

#endif // GUITEXTBUTTON_H
