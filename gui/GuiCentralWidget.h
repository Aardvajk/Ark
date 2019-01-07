#ifndef GUICENTRALWIDGET_H
#define GUICENTRALWIDGET_H

#include <QtWidgets/QWidget>

namespace QPx
{

class VBoxLayout;

}

class GuiCentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GuiCentralWidget(QWidget *parent = nullptr);

    QPx::VBoxLayout *layout() const;
};

#endif // GUICENTRALWIDGET_H
