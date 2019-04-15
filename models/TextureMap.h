#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H

#include "graphics/Graphics.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMap>

#include <vector>

class Model;

class TextureMap : public QObject
{
    Q_OBJECT

public:
    TextureMap(Model *model, Graphics *graphics, QObject *parent = nullptr);

    void add(const QString &file);
    void remove(const QString &file);

    void clear();

    const Gx::Texture &texture(const QString &file) const;

private:
    Model *model;
    Graphics *graphics;

    std::vector<Graphics::Handle<Gx::Texture> > v;
    QMap<QString, std::size_t> m;
    QVector<std::size_t> free;
};

#endif // TEXTUREMAP_H
