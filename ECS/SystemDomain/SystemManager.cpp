#include "SystemManager.hpp"

namespace ECS
{

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
        system->update();
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
