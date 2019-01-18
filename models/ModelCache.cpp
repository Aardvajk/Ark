#include "ModelCache.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include "properties/custom/Selection.h"

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

void ModelCache::invalidate()
{
    valid = false;
}

void ModelCache::refresh() const
{
    data.selected.clear();

    for(auto i: pcx::indexed_range(model->entities()))
    {
        if(i.value.properties()["Selection"].value<Selection>().any())
        {
            data.selected.append(static_cast<int>(i.index));
        }
    }

    valid = true;
}
