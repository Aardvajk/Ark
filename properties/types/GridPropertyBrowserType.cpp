#include "GridPropertyBrowserType.h"

#include "maths/Grid.h"

#include <QPxPropertyBrowser/QPxPropertyBrowserItem.h>

GridPropertyBrowserType::GridPropertyBrowserType(QObject *parent) : QPx::PropertyBrowserType(parent)
{
}

QString GridPropertyBrowserType::valueText(const QPx::PropertyBrowserItem *item) const
{
    auto g = item->value().value<Grid>();
    return g.valid() ? QString::number(g.value()) : QString();
}

int GridPropertyBrowserType::userType() const
{
    return qMetaTypeId<Grid>();
}

QPx::PropertyBrowserEditor *GridPropertyBrowserType::createEditor(const QPx::PropertyBrowserItem *item, QWidget *parent) const
{
    return nullptr;
}
