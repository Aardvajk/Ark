#include "PropertyView.h"

#include "models/PropertyModel.h"

#include <QPxPropertyBrowser/QPxPropertyBrowserDelegate.h>

PropertyView::PropertyView(PropertyModel *properties, QWidget *parent) : QTreeView(parent)
{
    setFrameStyle(QFrame::NoFrame);

    properties->setParent(this);
    setModel(properties);

    setItemDelegate(new QPx::PropertyBrowserDelegate(this));
}

PropertyView::~PropertyView()
{
    qDebug() << "delete propertyview";
}
