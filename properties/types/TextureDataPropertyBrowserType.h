#ifndef TEXTUREDATAPROPERTYBROWSERTYPE_H
#define TEXTUREDATAPROPERTYBROWSERTYPE_H

#include "properties/custom/TextureData.h"

#include <QPxPropertyBrowser/QPxPropertyBrowserType.h>

class Model;
class TexturePropertyBrowserType;
class Vec2PropertyBrowserType;

class TextureDataPropertyBrowserType : public QPx::PropertyBrowserType
{
    Q_OBJECT

public:
    TextureDataPropertyBrowserType(const Model *model, QObject *parent = nullptr);

    virtual void addProperties(QPx::PropertyBrowserItem *item, QPx::PropertyBrowserModel *model, const QModelIndex &parent) const override;
    virtual void updateProperties(QPx::PropertyBrowserItem *item, const QVariant &value) const override;

    virtual QString valueText(const QPx::PropertyBrowserItem *item) const override;
    virtual bool readOnly() const override;
    virtual int userType() const override;

private slots:
    void changed(const QVariant &value);

private:
    TexturePropertyBrowserType *diffuseType;
    TexturePropertyBrowserType *normalType;
    Vec2PropertyBrowserType *vecType;
};

#endif // TEXTUREDATAPROPERTYBROWSERTYPE_H
