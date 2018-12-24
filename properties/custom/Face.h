#ifndef FACE_H
#define FACE_H

#include <initializer_list>

#include <QtCore/QVector>

class Face
{
public:
    class Element
    {
    public:
        explicit Element(int index = -1) : index(index) { }

        bool operator==(const Element &e) const { return index == e.index; }
        bool operator!=(const Element &e) const { return index == e.index; }

        int index;
    };

    Face() = default;
    Face(std::initializer_list<int> indices){ for(auto i: indices) elements.append(Element(i)); }

    bool operator==(const Face &f) const { return elements == f.elements; }
    bool operator!=(const Face &f) const { return elements != f.elements; }

    QVector<Element> elements;
};

#endif // FACE_H
