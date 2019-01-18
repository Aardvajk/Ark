#include "ModelCache.h"

#include "models/Model.h"

ModelCache::ModelCache(Model *model, QObject *parent) : QObject(parent), model(model), valid(false)
{
    connect(model, SIGNAL(changed()), SLOT(invalidate()));
}

void ModelCache::invalidate()
{
    valid = false;
}
