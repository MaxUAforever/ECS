#include "EntityManager.hpp"

namespace ECS
{

IEntity* EntityManager::getEntity(const EntityID& id) const
{
    auto entityIt = _entitiesContainer.find(id);
    
    if (entityIt == _entitiesContainer.end())
    {
        return nullptr;
    }
    
    return entityIt->second.get();
}

void EntityManager::reset()
{
    _entitiesContainer.clear();
}

void EntityManager::removeEntity(const EntityID& id)
{
    _entitiesContainer.erase(id);
    notifyIsRemoved(id);
}

void EntityManager::notifyIsRemoved(const EntityID& id)
{
    for (auto observer : _observers)
    {
        observer->onEntityRemove(id);
    }
}

void EntityManager::registerObserver(IEntityManagerObserver* observer)
{
    _observers.push_back(observer);
}

} //namespace ECS
