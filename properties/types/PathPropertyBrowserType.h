#ifndef PATHPROPERTYBROWSERTYPE_H
#define PATHPROPERTYBROWSERTYPE_H

#include <QPxPropertyBrowser/QPxPropertyBrowserEditor.h>
#include <QPxPropertyBrowser/QPxPropertyBrowserType.h>

#include <pcx/aligned_store.h>

class QLineEdit;
class PathPropertyBrowserType;

class PathPropertyBrowserEditor : public QPx::PropertyBrowserEditor
{
    Q_OBJECT

public:
    PathPropertyBrowserEditor(const PathPropertyBrowserType *type, const QString &path, QWidget *parent = nullptr);

    virtual QVariant value() const override;
    virtual void setValue(const QVariant &value) override;

private slots:
    void buttonClicked();

private:
    const PathPropertyBrowserType *type;
    QLineEdit *edit;
};

class PathPropertyBrowserType : public QPx::PropertyBrowserType
{
    Q_OBJECT

public:
    enum class Type
    {
        Directory,
        File,
        ExistingFile
    };

    PathPropertyBrowserType(Type type, const QString &filter, QObject *parent = nullptr);

    Type type() const;
    QString filter() const;

    virtual int userType() const override;

    virtual QPx::PropertyBrowserEditor *createEditor(const QPx::PropertyBrowserItem *item, QWidget *parent) const override;

private:
    pcx::aligned_store<16> cache;
};

#endif // PATHPROPERTYBROWSERTYPE_H
