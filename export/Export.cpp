#include "Export.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include "graphics/vertices/PreviewVertex.h"

#include <QtGui/QColor>

#include <QGxMaths/QGxColor.h>

#include <GxMaths/GxColor.h>

#include <pcx/datastream.h>
#include <pcx/indexed_range.h>

#include <sstream>

pcx::data_ostream &operator<<(pcx::data_ostream &os, const Gx::Vec3 &v){ return os << v.x << v.y << v.z; }
pcx::data_ostream &operator<<(pcx::data_ostream &os, const QColor &v){ return os << float(v.redF()) << float(v.greenF()) << float(v.blueF()); }

bool exportModel(const QString &path, const Model *model)
{
    pcx::data_ofstream os(path.toStdString().c_str());
    if(!os.is_open())
    {
        return false;
    }

    QVector<Entity> geoms;

    for(const auto &e: model->entities())
    {
        switch(e.type())
        {
            case Entity::Type::Geometry: geoms.append(e); break;

            default: break;
        }
    }

    os << 1;

    std::ostringstream bm;
    pcx::data_ostream ms(&bm);

    unsigned bytes = 0;

    for(const auto &e: geoms)
    {
        const auto &mesh = e.mesh();

        QSet<int> visibles;
        for(int i = 0; i < mesh.faces.count(); ++i)
        {
            if(e.subProperty(Element::Type::Face, i, "Visible").value<bool>()) visibles.insert(i);
        }

        for(auto f: pcx::indexed_range(mesh.faces))
        {
            if(visibles.contains(f.index))
            {
                auto color = QGx::Color(e.subProperty(Element::Type::Face, f.index, "Color").value<QColor>());
                auto n = mesh.faceNormal(f.index);

                for(int i = 1; i < f.value.elements.count() - 1; ++i)
                {
                    ms << mesh.vertices[f.value.elements[0].index] << n << Gx::Rgba(color);
                    ms << mesh.vertices[f.value.elements[i].index] << n << Gx::Rgba(color);
                    ms << mesh.vertices[f.value.elements[i + 1].index] << n << Gx::Rgba(color);

                    bytes += sizeof(PreviewVertex) * 3;
                }
            }
        }
    }

    os << bytes;
    os.write(bm.str().data(), bm.str().size());

    return true;
}
