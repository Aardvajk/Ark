#ifndef GUILAYOUTWIDGET_H
#define GUILAYOUTWIDGET_H

#include <QtWidgets/QWidget>

class QLayout;

class GuiLayoutWidget : public QWidget
{
    Q_OBJECT

public:
    GuiLayoutWidget(QLayout *layout, QWidget *parent = nullptr);
};

#endif // GUILAYOUTWIDGET_H
