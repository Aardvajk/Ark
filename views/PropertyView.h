#ifndef PROPERTYVIEW_H
#define PROPERTYVIEW_H

#include <QtWidgets/QTreeView>

class PropertyModel;

class PropertyView : public QTreeView
{
    Q_OBJECT

public:
    PropertyView(PropertyModel *properties, QWidget *parent = nullptr);
};

#endif // PROPERTYVIEW_H
