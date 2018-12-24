#ifndef PROPERTY_H
#define PROPERTY_H

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
        ReadOnly = 2
    };

    using Flags = pcx::flags<Flag>;

    Property() = default;

    Property(int value, Flags flags = Flags()) : s(value, flags) { }
    Property(float value, Flags flags = Flags()) : s(value, flags) { }
    Property(const QString &value, Flags flags = Flags()) : s(value, flags) { }
    Property(const QColor &value, Flags flags = Flags()) : s(QVariant::fromValue(value), flags) { }

    int toInt() const { return s.value().value.toInt(); }
    float toFloat() const { return s.value().value.toFloat(); }
    QString toString() const { return s.value().value.toString(); }
    QColor toColor() const { return qvariant_cast<QColor>(s.value().value); }

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
