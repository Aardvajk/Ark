#ifndef SELECTION_H
#define SELECTION_H

#include <QtCore/QSet>
#include <QtCore/QMetaType>

class Selection
{
public:
    enum class Type
    {
        None,
        Object,
        Face,
        Vertex,
        Invalid
    };

    explicit Selection(bool object = false) : object(object) { }
    Selection(const QSet<int> &faces, const QSet<int> &vertices) : object(false), faces(faces), vertices(vertices) { }

    bool operator==(const Selection &s) const;
    bool operator!=(const Selection &s) const;
    bool operator<(const Selection &s) const;

    Selection merge(const Selection &s) const;
    Selection remove(const Selection &s) const;

    bool any() const;

    static const char *typeToString(Type type);
    static Type typeFromString(const std::string &text);

    bool object;
    QSet<int> faces;
    QSet<int> vertices;
};

Q_DECLARE_METATYPE(Selection)

#endif // SELECTION_H
