#ifndef GUISEPARATOR_H
#define GUISEPARATOR_H

#include <QtWidgets/QWidget>

class GuiSeparator : public QWidget
{
    Q_OBJECT

public:
    enum class Style { Line, StyledLine };

    GuiSeparator(Style style, Qt::Orientation orientation, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    Style style;
};

#endif // GUISEPARATOR_H
