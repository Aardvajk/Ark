#include "TexturePropertyBrowserType.h"

#include "models/Model.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QPxPropertyBrowser/QPxPropertyBrowserItem.h>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QToolButton>

TexturePropertyBrowserEditor::TexturePropertyBrowserEditor(const Model *model, Entity::Type type, const QString &path, QWidget *parent) : QPx::PropertyBrowserEditor(parent), model(model), type(type)
{
    auto layout = new QPx::HBoxLayout(this);

    combo = layout->addTypedWidget(new QComboBox());
    setFocusProxy(combo);

    combo->addItem("(None)");

    int index = -1;
    if(path.isEmpty())
    {
        index = 0;
    }

    for(int i: model->resources())
    {
        auto e = model->entities()[i];
        if(e.type() == type)
        {
            auto file = e.property("Path").value<QString>();
            if(path == file)
            {
                index = combo->count();
            }

            combo->addItem(QIcon(e.property("Thumbnail").value<QPixmap>()), file);
        }
    }

    if(index < 0)
    {
        index = 1;
        combo->insertItem(1, path);
    }

    combo->setCurrentIndex(index);
    connect(combo, SIGNAL(currentIndexChanged(int)), SLOT(comboChanged(int)));
}

QVariant TexturePropertyBrowserEditor::value() const
{
    return combo->currentIndex() > 0 ? combo->itemText(combo->currentIndex()) : QString();
}

void TexturePropertyBrowserEditor::setValue(const QVariant &value)
{
    for(int i = 0; i < combo->count(); ++i)
    {
        if(combo->itemText(i) == value.toString())
        {
            auto g = pcx::scoped_lock(lock);
            combo->setCurrentIndex(i);
        }
    }
}

void TexturePropertyBrowserEditor::comboChanged(int index)
{
    if(!lock)
    {
        emit commit();
    }
}

TexturePropertyBrowserType::TexturePropertyBrowserType(const Model *model, Entity::Type type, QObject *parent) : QPx::PropertyBrowserType(parent), model(model), type(type)
{
}

int TexturePropertyBrowserType::userType() const
{
    return QMetaType::QString;
}

QPx::PropertyBrowserEditor *TexturePropertyBrowserType::createEditor(const QPx::PropertyBrowserItem *item, QWidget *parent) const
{
    return new TexturePropertyBrowserEditor(model, type, item->value().toString(), parent);
}
