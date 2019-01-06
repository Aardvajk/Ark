#ifndef GUITOOLBUTTON_H
#define GUITOOLBUTTON_H

#include "gui/GuiButton.h"

class GuiToolButton : public GuiButton
{
    Q_OBJECT

public:
    GuiToolButton(const QString &text, const QPixmap &pixmap, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QString text;
    QPixmap pixmap;
};

#endif // GUITOOLBUTTON_H
