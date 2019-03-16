#ifndef FACE_H
#define FACE_H

#include <initializer_list>

#include <GxMaths/GxVector.h>

#include <QtCore/QVector>

class Face
{
public:
    class Element
    {
    public:
        explicit Element(int index = -1) : index(index) { }

        int index;
        Gx::Vec2 texCoords;
    };

    Face() = default;
    Face(std::initializer_list<int> indices){ for(auto i: indices) elements.append(Element(i)); }

    QVector<Element> elements;
};

#endif // FACE_H
