#ifndef PROPERTY_H
#define PROPERTY_H

#include <pcx/flags.h>
#include <pcx/shared_data.h>

#include <QGxMaths/QGxMathsMetatypes.h>

#include <QtCore/QVariant>

class Property
{
public:
    enum class SubType
    {
        General,
        Directory
    };

    enum class Flag
    {
        Hidden = 1,
        ReadOnly = 2,
        NonPersistent = 4
    };

    using Flags = pcx::flags<Flag>;

    Property() = default;
    template<typename T> explicit Property(const T &value, Flags flags = Flags()) : s(SubType::General, QVariant::fromValue(value), flags) { }
    explicit Property(const char *value, Flags flags = Flags()) : s(SubType::General, QString(value), flags) { }
    template<typename T> explicit Property(SubType subType, const T &value, Flags flags = Flags()) : s(subType, QVariant::fromValue(value), flags) { }

    template<typename T> void setValue(const T &value){ s.value().value = QVariant::fromValue(value); }

    SubType subType() const { return s.value().subType; }
    template<typename T> T value() const { return s.value().value.value<T>(); }
    Flags flags() const { return s.value().flags; }

private:
    struct Data
    {
        SubType subType;
        QVariant value;
        Flags flags;
    };

    pcx::shared_data<Data> s;
};

template<> QVariant Property::value<QVariant>() const { return s.value().value; }

template<> struct pcx_is_flag_enum<Property::Flag> : std::true_type { };

#endif // PROPERTY_H
