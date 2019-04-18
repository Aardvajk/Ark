#include "RotateButtonBox.h"

#include "models/Model.h"

#include "gui/GuiTextButton.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtWidgets/QLabel>

namespace
{

class Button : public GuiTextButton
{
public:
    Button(const QString &text, int axis) : GuiTextButton(text), a(axis) { setFixedHeight(22); }

    int axis() const { return a; }

private:
    int a;
};

}

RotateButtonBox::RotateButtonBox(Model *model, QWidget *parent) : QWidget(parent), model(model)
{
    auto layout = new QPx::VBoxLayout(0, 2, this);

    auto row = layout->addTypedLayout(new QPx::HBoxLayout(0, 2));

    row->addWidget(new QLabel("Rotate:"));

    connect(row->addTypedWidget(new Button("X", 0)), SIGNAL(clicked()), SLOT(clicked()));
    connect(row->addTypedWidget(new Button("Y", 1)), SIGNAL(clicked()), SLOT(clicked()));
    connect(row->addTypedWidget(new Button("Z", 2)), SIGNAL(clicked()), SLOT(clicked()));

    connect(model, SIGNAL(changed()), SLOT(modelChanged()));

    modelChanged();
}

void RotateButtonBox::modelChanged()
{
    setEnabled(!model->objects().isEmpty());
}

void RotateButtonBox::clicked()
{
    emit rotate(dynamic_cast<const Button*>(sender())->axis());
}
