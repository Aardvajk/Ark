#include "PathPropertyBrowserType.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QPxPropertyBrowser/QPxPropertyBrowserItem.h>

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QFileDialog>

namespace
{

class Cache
{
public:
    Cache(PathPropertyBrowserType::Type type, const QString &filter) : type(type), filter(filter) { }

    PathPropertyBrowserType::Type type;
    QString filter;
};

}

PathPropertyBrowserEditor::PathPropertyBrowserEditor(const PathPropertyBrowserType *type, const QString &path, QWidget *parent) : QPx::PropertyBrowserEditor(parent), type(type)
{
    auto layout = new QPx::HBoxLayout(this);

    edit = layout->addTypedWidget(new QLineEdit());
    edit->setText(path);
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
    QString path;

    if(type->type() == PathPropertyBrowserType::Type::Directory)
    {
        path = QFileDialog::getExistingDirectory(this, "Select Directory", edit->text());
    }
    else if(type->type() == PathPropertyBrowserType::Type::File)
    {
        path = QFileDialog::getSaveFileName(this, "Select File", edit->text(), type->filter());
    }
    else if(type->type() == PathPropertyBrowserType::Type::ExistingFile)
    {
        path = QFileDialog::getOpenFileName(this, "Select File", edit->text(), type->filter());
    }

    if(!path.isEmpty())
    {
        edit->setText(path);
        emit commit();
    }
}

PathPropertyBrowserType::PathPropertyBrowserType(Type type, const QString &filter, QObject *parent) : QPx::PropertyBrowserType(parent)
{
    cache.alloc<Cache>(type, filter);
}

PathPropertyBrowserType::Type PathPropertyBrowserType::type() const
{
    return cache.get<Cache>().type;
}

QString PathPropertyBrowserType::filter() const
{
    return cache.get<Cache>().filter;
}

int PathPropertyBrowserType::userType() const
{
    return QMetaType::QString;
}

QPx::PropertyBrowserEditor *PathPropertyBrowserType::createEditor(const QPx::PropertyBrowserItem *item, QWidget *parent) const
{
    return new PathPropertyBrowserEditor(this, item->value().toString(), parent);
}
