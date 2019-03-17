#ifndef TEXTUREPROPERTYBROWSERTYPE_H
#define TEXTUREPROPERTYBROWSERTYPE_H

#include <QPxPropertyBrowser/QPxPropertyBrowserEditor.h>
#include <QPxPropertyBrowser/QPxPropertyBrowserType.h>

class Model;
class QLineEdit;

class TexturePropertyBrowserEditor : public QPx::PropertyBrowserEditor
{
    Q_OBJECT

public:
    TexturePropertyBrowserEditor(const Model *model, const QString &path, QWidget *parent = nullptr);

    virtual QVariant value() const override;
    virtual void setValue(const QVariant &value) override;

private slots:
    void buttonClicked();

private:
    const Model *model;
    QLineEdit *edit;
};

class TexturePropertyBrowserType : public QPx::PropertyBrowserType
{
    Q_OBJECT

public:
    TexturePropertyBrowserType(const Model *model, QObject *parent = nullptr);

    virtual int userType() const override;

    virtual QPx::PropertyBrowserEditor *createEditor(const QPx::PropertyBrowserItem *item, QWidget *parent) const override;

private:
    const Model *model;
};

#endif // TEXTUREPROPERTYBROWSERTYPE_H
