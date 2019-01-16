#ifndef PROPERTY_H
#define PROPERTY_H

#include <pcx/flags.h>
#include <pcx/shared_data.h>

#include <QGxMaths/QGxMathsMetatypes.h>

#include <QtCore/QVariant>

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
    template<typename T> explicit Property(const T &value, Flags flags = Flags()) : s(QVariant::fromValue(value), flags) { }
    explicit Property(const char *value, Flags flags = Flags()) : s(QString(value), flags) { }

    template<typename T> void setValue(const T &value){ s.value().value = QVariant::fromValue(value); }

    template<typename T> T value() const { return s.value().value.value<T>(); }
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
