#include "ComponentManager.hpp"

namespace ECS
{

IComponent* ComponentManager::getComponent(const ComponentID& id) const
{
    auto componentIt = _components.find(id);
    if (componentIt == _components.end())
    {
        return nullptr;
    }
    
    return componentIt->second.get();
}

void ComponentManager::remove(const EntityID& entityID, const ComponentID& componentID)
{
    auto componentsIt = _entitiesMap.find(entityID);
    if (componentsIt == _entitiesMap.end())
    {
        return;
    }
    
    componentsIt->second.erase(componentID);
    _components.erase(componentID);
}

void ComponentManager::clearEntity(const EntityID& entityID)
{
    auto componentsIt = _entitiesMap.find(entityID);
    if (componentsIt == _entitiesMap.end())
    {
        return;
    }
    
    auto& componentIDs = componentsIt->second;
    for (const auto& componentID : componentIDs)
    {
        _components.erase(componentID);
    }
    
    componentIDs.clear();
}

void ComponentManager::reset()
{
    _components.clear();
    _entitiesMap.clear();
}

void ComponentManager::onEntityRemove(const EntityID& entityID)
{
    clearEntity(entityID);
}

} // namespace ECS
