#ifndef PATHPROPERTYBROWSERTYPE_H
#define PATHPROPERTYBROWSERTYPE_H

#include <QPxPropertyBrowser/QPxPropertyBrowserEditor.h>
#include <QPxPropertyBrowser/QPxPropertyBrowserType.h>

class QLineEdit;

class PathPropertyBrowserEditor : public QPx::PropertyBrowserEditor
{
    Q_OBJECT

public:
    explicit PathPropertyBrowserEditor(QWidget *parent = nullptr);

    virtual QVariant value() const override;
    virtual void setValue(const QVariant &value) override;

private slots:
    void buttonClicked();

private:
    QLineEdit *edit;
};

class PathPropertyBrowserType : public QPx::PropertyBrowserType
{
    Q_OBJECT

public:
    explicit PathPropertyBrowserType(QObject *parent = nullptr);

    virtual int userType() const override;

    virtual QPx::PropertyBrowserEditor *createEditor(const QPx::PropertyBrowserItem *item, QWidget *parent) const override;
};

#endif // PATHPROPERTYBROWSERTYPE_H
