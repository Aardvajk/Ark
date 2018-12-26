#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "entity/Entity.h"

namespace EntityFactory
{

Entity create(Entity::Type type);
void updateMesh(Entity &entity);

}

#endif // ENTITYFACTORY_H
