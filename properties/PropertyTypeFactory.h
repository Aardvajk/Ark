#ifndef PROPERTYTYPEFACTORY_H
#define PROPERTYTYPEFACTORY_H

#include <QtCore/QObject>

#include <pcx/aligned_store.h>

namespace QPx
{

class PropertyBrowserType;

}

class Property;

class PropertyTypeFactory : public QObject
{
    Q_OBJECT

public:
    explicit PropertyTypeFactory(QObject *parent = nullptr);

    QPx::PropertyBrowserType *type(const Property &property) const;

private:
    pcx::aligned_store<16> cache;
};

#endif // PROPERTYTYPEFACTORY_H
