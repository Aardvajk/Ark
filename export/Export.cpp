#include "Export.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include "properties/custom/TextureData.h"

#include "graphics/RenderKey.h"

#include "graphics/vertices/PreviewVertex.h"

#include "maths/Tangent.h"

#include <QtGui/QColor>

#include <QGxMaths/QGxColor.h>

#include <GxMaths/GxColor.h>

#include <QtCore/QHash>

#include <pcx/datastream.h>
#include <pcx/indexed_range.h>

#include <sstream>

namespace
{

Gx::Vec3 average(const QVector<Gx::Vec3> &vs)
{
    Gx::Vec3 a(0, 0, 0);
    for(auto v: vs)
    {
        a += v;
    }

    return a / static_cast<float>(vs.count());
}

}

pcx::data_ostream &operator<<(pcx::data_ostream &os, const QColor &v){ return os << float(v.redF()) << float(v.greenF()) << float(v.blueF()); }
pcx::data_ostream &operator<<(pcx::data_ostream &os, const QString &v){ return os << v.toStdString(); }

bool exportModel(const QString &path, const Model *model)
{
    pcx::data_ofstream os(path.toStdString().c_str());
    if(!os.is_open())
    {
        return false;
    }

    QVector<int> geoms;

    for(const auto &e: pcx::indexed_range(model->entities()))
    {
        switch(e.value.type())
        {
            case Entity::Type::Geometry: geoms.append(e.index); break;

            default: break;
        }
    }

    os << 1;

    os << model->property("Light").value<Gx::Vec3>();

    for(auto index: geoms)
    {
        const auto &e = model->entities()[index];
        const auto &mesh = e.mesh();
        auto pos = average(mesh.vertices);

        os << "staticpolyhedron" << QString() << pos;

        os << std::size_t(mesh.vertices.count());
        for(auto v: mesh.vertices) os << Gx::Vec3(v - pos);

        os << std::size_t(mesh.faces.count());
        for(auto f: mesh.faces)
        {
            os << std::size_t(f.elements.count());
            for(auto e: f.elements) os << std::size_t(e.index);
        }
    }

    QHash<RenderKey, QVector<QPair<int, int> > > groups;

    QSet<QString> textures;

    for(auto index: geoms)
    {
        const auto &e = model->entities()[index];
        const auto &mesh = e.mesh();

        QSet<int> visibles;
        for(int i = 0; i < mesh.faces.count(); ++i)
        {
            if(e.subProperty(Element::Type::Face, i, "Visible").value<bool>())
            {
                RenderKey key;

                key.group = e.property("Group").value<QString>();
                key.diffuse = e.subProperty(Element::Type::Face, i, "Texture").value<TextureData>().diffuse;
                key.normal = e.subProperty(Element::Type::Face, i, "Texture").value<TextureData>().normal;

                if(!key.diffuse.isEmpty())
                {
                    textures.insert(key.diffuse);
                }

                if(!key.normal.isEmpty())
                {
                    textures.insert(key.normal);
                }

                groups[key].append(qMakePair(index, i));
            }
        }
    }

    int textureId = 1;
    QHash<QString, QString> textureIds;

    for(auto texture: textures)
    {
        auto id = QString("texture%1").arg(textureId++);
        textureIds[texture] = id;

        os << "texture" << id << texture;
    }

    int meshId = 1;

    for(auto key: groups.keys())
    {
        std::ostringstream bm;
        pcx::data_ostream ms(&bm);

        unsigned bytes = 0;

        for(auto pair: groups[key])
        {
            const auto &e = model->entities()[pair.first];
            const auto &mesh = e.mesh();

            const auto &f = mesh.faces[pair.second];

            auto color = QGx::Color(e.subProperty(Element::Type::Face, pair.second, "Color").value<QColor>());
            auto n = mesh.faceNormal(pair.second);

            for(int i = 1; i < f.elements.count() - 1; ++i)
            {
                auto v0 = mesh.vertices[f.elements[0].index];
                auto v1 = mesh.vertices[f.elements[i].index];
                auto v2 = mesh.vertices[f.elements[i + 1].index];

                auto t0 = f.elements[0].texCoords;
                auto t1 = f.elements[i].texCoords;
                auto t2 = f.elements[i + 1].texCoords;

                auto t = calculateTangent(v0, t0, v1, t2, v2, t2, n);

                ms << v0 << n << Gx::Rgba(color) << t0 << t;
                ms << v1 << n << Gx::Rgba(color) << t1 << t;
                ms << v2 << n << Gx::Rgba(color) << t2 << t;

                bytes += sizeof(PreviewVertex) * 3;
            }
        }

        if(bytes)
        {
            auto id = QString("mesh%1").arg(meshId++);

            os << "internalmesh" << id;
            os << bytes;
            os.write(bm.str().data(), bm.str().size());

            os << "staticmeshinstance" << id << textureIds[key.diffuse] << textureIds[key.normal] << Gx::Vec3(0, 0, 0);
        }
    }

    os << "";

    return true;
}
