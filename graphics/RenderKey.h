#ifndef RENDERKEY_H
#define RENDERKEY_H

#include <QtCore/QString>

class RenderKey
{
public:
    RenderKey() = default;

    bool operator==(const RenderKey &o) const;

    QString group;
    QString diffuse;
    QString normal;
};

uint qHash(const RenderKey &v);

#endif // RENDERKEY_H
