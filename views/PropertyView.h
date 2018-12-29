#ifndef PROPERTYVIEW_H
#define PROPERTYVIEW_H

#include <QtWidgets/QTreeView>

class PropertyView : public QTreeView
{
    Q_OBJECT

public:
    explicit PropertyView(QWidget *parent = nullptr);
};

#endif // PROPERTYVIEW_H
