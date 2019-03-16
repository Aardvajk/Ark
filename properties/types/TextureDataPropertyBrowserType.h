#ifndef TEXTUREDATAPROPERTYBROWSERTYPE_H
#define TEXTUREDATAPROPERTYBROWSERTYPE_H

#include "core/TextureData.h"

#include <QPxPropertyBrowser/QPxPropertyBrowserType.h>

class Vec2PropertyBrowserType;

class TextureDataPropertyBrowserType : public QPx::PropertyBrowserType
{
    Q_OBJECT

public:
    explicit TextureDataPropertyBrowserType(QObject *parent = nullptr);

    virtual void addProperties(QPx::PropertyBrowserItem *item, QPx::PropertyBrowserModel *model, const QModelIndex &parent) const override;
    virtual void updateProperties(QPx::PropertyBrowserItem *item, const QVariant &value) const override;

    virtual QString valueText(const QPx::PropertyBrowserItem *item) const override;
    virtual bool readOnly() const override;
    virtual int userType() const override;

private slots:
    void changed(const QVariant &value);

private:
    Vec2PropertyBrowserType *type;
};

#endif // TEXTUREDATAPROPERTYBROWSERTYPE_H
