#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "entity/Entity.h"

namespace EntityFactory
{

Entity create(Entity::Type type);

}

#endif // ENTITYFACTORY_H
