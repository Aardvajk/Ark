#ifndef GUILARGEBUTTON_H
#define GUILARGEBUTTON_H

#include "gui/GuiButton.h"

class GuiLargeButton : public GuiButton
{
    Q_OBJECT

public:
    GuiLargeButton(const QString &text, const QPixmap &pixmap, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QString text;
    QPixmap pixmap;
};

#endif // GUILARGEBUTTON_H
