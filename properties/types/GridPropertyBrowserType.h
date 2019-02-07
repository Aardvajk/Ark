#ifndef GRIDPROPERTYBROWSERTYPE_H
#define GRIDPROPERTYBROWSERTYPE_H

#include <QPxPropertyBrowser/QPxPropertyBrowserType.h>

class GridPropertyBrowserType : public QPx::PropertyBrowserType
{
    Q_OBJECT

public:
    explicit GridPropertyBrowserType(QObject *parent = nullptr);

    virtual QString valueText(const QPx::PropertyBrowserItem *item) const override;
    virtual int userType() const override;

    virtual QPx::PropertyBrowserEditor *createEditor(const QPx::PropertyBrowserItem *item, QWidget *parent) const override;
};

#endif // GRIDPROPERTYBROWSERTYPE_H
