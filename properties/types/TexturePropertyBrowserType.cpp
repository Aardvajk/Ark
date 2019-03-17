#include "TexturePropertyBrowserType.h"

#include "models/Model.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QPxPropertyBrowser/QPxPropertyBrowserItem.h>

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QFileDialog>

TexturePropertyBrowserEditor::TexturePropertyBrowserEditor(const Model *model, const QString &path, QWidget *parent) : QPx::PropertyBrowserEditor(parent), model(model)
{
    auto layout = new QPx::HBoxLayout(this);

    edit = layout->addTypedWidget(new QLineEdit());
    edit->setText(path);
    setFocusProxy(edit);

    auto button = layout->addTypedWidget(new QToolButton());
    button->setText("...");

    connect(button, SIGNAL(clicked()), SLOT(buttonClicked()));
}

QVariant TexturePropertyBrowserEditor::value() const
{
    return edit->text();
}

void TexturePropertyBrowserEditor::setValue(const QVariant &value)
{
    edit->setText(value.toString());
}

void TexturePropertyBrowserEditor::buttonClicked()
{
    auto base = model->property("Textures").value<QString>();

    if(!base.isEmpty())
    {
        auto path = QFileDialog::getOpenFileName(this, "Select Texture", base + QDir::separator() + edit->text(), "Images (*.png)");
        if(!path.isEmpty())
        {
            edit->setText(QFileInfo(path).fileName());
            emit commit();
        }
    }
}

TexturePropertyBrowserType::TexturePropertyBrowserType(const Model *model, QObject *parent) : QPx::PropertyBrowserType(parent), model(model)
{
}

int TexturePropertyBrowserType::userType() const
{
    return QMetaType::QString;
}

QPx::PropertyBrowserEditor *TexturePropertyBrowserType::createEditor(const QPx::PropertyBrowserItem *item, QWidget *parent) const
{
    return new TexturePropertyBrowserEditor(model, item->value().toString(), parent);
}
