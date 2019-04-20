#ifndef MODELMAP_H
#define MODELMAP_H

#include "graphics/Graphics.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMap>

#include <vector>

class Model;

class ModelMap : public QObject
{
    Q_OBJECT

public:
    ModelMap(Model *model, Graphics *graphics, QObject *parent = nullptr);

    void add(const QString &file);
    void remove(const QString &file);

    void clear();

private:
    Model *model;
    Graphics *graphics;

    std::vector<Graphics::Handle<Gx::VertexBuffer> > v;
    QMap<QString, std::size_t> m;
    QVector<std::size_t> free;
};

#endif // MODELMAP_H
