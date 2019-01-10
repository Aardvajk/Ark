#ifndef LAYOUTOPTIONSWIDGET_H
#define LAYOUTOPTIONSWIDGET_H

#include <QtWidgets/QWidget>

class ActionList;
class LayoutDiagram;

class LayoutOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    LayoutOptionsWidget(ActionList *actions, QWidget *parent = nullptr);

signals:
    void changed();

public slots:
    void commit();

private:
    LayoutDiagram *diagram;
};

#endif // LAYOUTOPTIONSWIDGET_H
