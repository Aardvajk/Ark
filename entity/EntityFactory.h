#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "entity/Entity.h"

class PropertyMap;

namespace EntityFactory
{

Entity create(Entity::Type type);

void defaultFaceProperties(PropertyMap &properties);

}

#endif // ENTITYFACTORY_H
