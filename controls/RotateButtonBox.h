#ifndef ROTATEBUTTONBOX_H
#define ROTATEBUTTONBOX_H

#include <QtWidgets/QWidget>

class Model;

class RotateButtonBox : public QWidget
{
    Q_OBJECT

public:
    RotateButtonBox(Model *model, QWidget *parent = nullptr);

signals:
    void rotate(int axis);

private slots:
    void modelChanged();
    void clicked();

private:
    Model *model;
};

#endif // ROTATEBUTTONBOX_H
