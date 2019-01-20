#ifndef VEC3PROPERTYBROWSERTYPE_H
#define VEC3PROPERTYBROWSERTYPE_H

#include <QPxPropertyBrowser/QPxPropertyBrowserType.h>

#include <GxMaths/GxVector.h>

class Vec3PropertyBrowserType : public QPx::PropertyBrowserType
{
    Q_OBJECT

public:
    explicit Vec3PropertyBrowserType(QObject *parent = nullptr);

    virtual void addProperties(QPx::PropertyBrowserItem *item, QPx::PropertyBrowserModel *model, const QModelIndex &parent) const override;
    virtual void updateProperties(QPx::PropertyBrowserItem *item, const QVariant &value) const override;

    virtual QString valueText(const QPx::PropertyBrowserItem *item) const override;
    virtual bool readOnly() const override;
    virtual int userType() const override;

private slots:
    void changed(const QVariant &value);

private:
    QPx::FloatPropertyBrowserType *type;
};

#endif // VEC3PROPERTYBROWSERTYPE_H
