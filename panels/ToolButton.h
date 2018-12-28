#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include "gui/GuiButton.h"

class ToolButton : public GuiButton
{
    Q_OBJECT

public:
    ToolButton(const QString &text, const QPixmap &pixmap, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QString text;
    QPixmap pixmap;
};

#endif // TOOLBUTTON_H
