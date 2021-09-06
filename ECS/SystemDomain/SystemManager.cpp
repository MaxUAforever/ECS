#include "SystemManager.hpp"

namespace ECS
{
SystemManager::SystemManager(const EventManager& eventManager)
    : _eventManager{eventManager}
{
}

ISystem* SystemManager::getSystem(const SystemID& id) const
{
    auto systemIt = _systems.find(id);
    if (systemIt == _systems.end())
    {
        return nullptr;
    }
    
    return systemIt->second.get();
}

void SystemManager::updateSystems()
{
    for (auto& systemValue : _systems)
    {
        auto& system = systemValue.second;
        auto event = system->update();
        
        _eventManager.handleEvent(std::move(event));
    }
}

void SystemManager::reset()
{
    _systems.clear();
}

void SystemManager::removeSystem(const SystemID& id)
{
    _systems.erase(id);
}

} // namespace ECS
