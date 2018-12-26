#ifndef GUISEPARATOR_H
#define GUISEPARATOR_H

#include <QtWidgets/QWidget>

class GuiSeparator : public QWidget
{
    Q_OBJECT

public:
    GuiSeparator(Qt::Orientation orientation, QWidget *parent = nullptr);
};

#endif // GUISEPARATOR_H
