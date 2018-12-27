#ifndef PROPERTY_H
#define PROPERTY_H

#include "properties/custom/Selection.h"
#include "properties/custom/Mesh.h"

#include <pcx/flags.h>
#include <pcx/shared_data.h>

#include <QtCore/QVariant>

#include <QtGui/QColor>

class Property
{
public:
    enum class Flag
    {
        Hidden = 1,
        ReadOnly = 2,
        NonPersistent = 4
    };

    using Flags = pcx::flags<Flag>;

    Property() = default;

    explicit Property(int value, Flags flags = Flags()) : s(value, flags) { }
    explicit Property(float value, Flags flags = Flags()) : s(value, flags) { }
    explicit Property(bool value, Flags flags = Flags()) : s(value, flags) { }
    explicit Property(const QString &value, Flags flags = Flags()) : s(value, flags) { }
    explicit Property(const char *value, Flags flags = Flags()) : s(QString(value), flags) { }
    explicit Property(const QColor &value, Flags flags = Flags()) : s(QVariant::fromValue(value), flags) { }
    explicit Property(const Selection &value, Flags flags = Flags()) : s(QVariant::fromValue(value), flags) { }
    explicit Property(const Mesh &value, Flags flags = Flags()) : s(QVariant::fromValue(value), flags) { }

    int toInt() const { return s.value().value.toInt(); }
    float toFloat() const { return s.value().value.toFloat(); }
    bool toBool() const { return s.value().value.toBool(); }
    QString toString() const { return s.value().value.toString(); }
    QColor toColor() const { return qvariant_cast<QColor>(s.value().value); }
    Selection toSelection() const { return qvariant_cast<Selection>(s.value().value); }
    Mesh toMesh() const { return qvariant_cast<Mesh>(s.value().value); }

    void setValue(int value){ s.value().value = value; }
    void setValue(float value){ s.value().value = value; }
    void setValue(bool value){ s.value().value = value; }
    void setValue(const QString &value){ s.value().value = value; }
    void setValue(const QColor &value){ s.value().value = QVariant::fromValue(value); }
    void setValue(const Selection &value){ s.value().value = QVariant::fromValue(value); }
    void setValue(const Mesh &value){ s.value().value = QVariant::fromValue(value); }

    Flags flags() const { return s.value().flags; }

private:
    struct Data
    {
        QVariant value;
        Flags flags;
    };

    pcx::shared_data<Data> s;
};

template<> struct pcx_is_flag_enum<Property::Flag> : std::true_type { };

#endif // PROPERTY_H
