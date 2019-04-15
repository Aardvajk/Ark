#include "ModelCache.h"

#include "core/Selection.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include <pcx/indexed_range.h>

ModelCache::ModelCache(Model *model, QObject *parent) : QObject(parent), model(model), valid(false)
{
    connect(model, SIGNAL(changed()), SLOT(invalidate()));
}

QVector<int> ModelCache::selected() const
{
    if(!valid)
    {
        refresh();
    }

    return data.selected;
}

QVector<int> ModelCache::objects() const
{
    if(!valid)
    {
        refresh();
    }

    return data.objects;
}

QVector<int> ModelCache::resources() const
{
    if(!valid)
    {
        refresh();
    }

    return data.resources;
}

void ModelCache::invalidate()
{
    valid = false;
}

void ModelCache::refresh() const
{
    data = { };

    for(auto i: pcx::indexed_range(model->entities()))
    {
        if(i.value.selection().any())
        {
            data.selected.append(static_cast<int>(i.index));
        }

        if(i.value.selection().elements[Element::Type::Face].count() && i.value.selection().elements[Element::Type::Face].count() == i.value.mesh().faces.count())
        {
            data.objects.append(static_cast<int>(i.index));
        }

        if(Entity::isResourceType(i.value.type()))
        {
            data.resources.append(static_cast<int>(i.index));
        }
    }

    valid = true;
}
