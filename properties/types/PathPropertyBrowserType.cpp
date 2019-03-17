#include "PathPropertyBrowserType.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QFileDialog>

PathPropertyBrowserEditor::PathPropertyBrowserEditor(QWidget *parent) : QPx::PropertyBrowserEditor(parent)
{
    auto layout = new QPx::HBoxLayout(this);

    edit = layout->addTypedWidget(new QLineEdit());
    setFocusProxy(edit);

    auto button = layout->addTypedWidget(new QToolButton());
    button->setText("...");

    connect(button, SIGNAL(clicked()), SLOT(buttonClicked()));
}

QVariant PathPropertyBrowserEditor::value() const
{
    return edit->text();
}

void PathPropertyBrowserEditor::setValue(const QVariant &value)
{
    edit->setText(value.toString());
}

void PathPropertyBrowserEditor::buttonClicked()
{
    auto path = QFileDialog::getExistingDirectory(this, "Select Directory");
    if(!path.isEmpty())
    {
        edit->setText(path);
        emit commit();
    }
}

PathPropertyBrowserType::PathPropertyBrowserType(QObject *parent) : QPx::PropertyBrowserType(parent)
{
}

int PathPropertyBrowserType::userType() const
{
    return QMetaType::QString;
}

QPx::PropertyBrowserEditor *PathPropertyBrowserType::createEditor(const QPx::PropertyBrowserItem *item, QWidget *parent) const
{
    return new PathPropertyBrowserEditor(parent);
}
