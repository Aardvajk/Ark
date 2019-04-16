#ifndef TEXTUREPROPERTYBROWSERTYPE_H
#define TEXTUREPROPERTYBROWSERTYPE_H

#include "entity/Entity.h"

#include <QPxPropertyBrowser/QPxPropertyBrowserEditor.h>
#include <QPxPropertyBrowser/QPxPropertyBrowserType.h>

#include <pcx/scoped_lock.h>

class Model;
class QComboBox;

class TexturePropertyBrowserEditor : public QPx::PropertyBrowserEditor
{
    Q_OBJECT

public:
    TexturePropertyBrowserEditor(const Model *model, Entity::Type type, const QString &path, QWidget *parent = nullptr);

    virtual QVariant value() const override;
    virtual void setValue(const QVariant &value) override;

private slots:
    void comboChanged(int index);

private:
    const Model *model;
    Entity::Type type;
    QComboBox *combo;
    pcx::lock lock;
};

class TexturePropertyBrowserType : public QPx::PropertyBrowserType
{
    Q_OBJECT

public:
    TexturePropertyBrowserType(const Model *model, Entity::Type type, QObject *parent = nullptr);

    virtual int userType() const override;

    virtual QPx::PropertyBrowserEditor *createEditor(const QPx::PropertyBrowserItem *item, QWidget *parent) const override;

private:
    const Model *model;
    Entity::Type type;
};

#endif // TEXTUREPROPERTYBROWSERTYPE_H
