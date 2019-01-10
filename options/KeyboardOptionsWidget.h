#ifndef KEYBOARDOPTIONSWIDGET_H
#define KEYBOARDOPTIONSWIDGET_H

#include <QtWidgets/QWidget>

class ActionList;

namespace QPx
{

class KeyboardOptionsWidget;

}

class KeyboardOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    KeyboardOptionsWidget(ActionList *actions, QWidget *parent = nullptr);

signals:
    void changed();

public slots:
    void commit();

private:
    QPx::KeyboardOptionsWidget *keyboard;
};

#endif // KEYBOARDOPTIONSWIDGET_H
