#include "PropertyView.h"

#include "models/PropertyModel.h"

#include <QPxPropertyBrowser/QPxPropertyBrowserDelegate.h>

PropertyView::PropertyView(PropertyModel *properties, QWidget *parent) : QTreeView(parent)
{
    setFrameStyle(QFrame::NoFrame);
    setModel(properties);
    setRootIsDecorated(false);
    setItemDelegate(new QPx::PropertyBrowserDelegate(this));
}
