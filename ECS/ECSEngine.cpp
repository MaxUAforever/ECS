#include "ECSEngine.hpp"

namespace ECS
{

ECSEngine::ECSEngine()
    : _entityManager()
    , _systemManager()
    , _componentManager(_entityManager)
    , _eventManager(_systemManager)
{
}

EntityManager& ECSEngine::getEntityManager()
{
    return _entityManager;
}

ComponentManager& ECSEngine::getComponentManager()
{
    return _componentManager;
}

SystemManager& ECSEngine::getSystemManager()
{
    return _systemManager;
}

EventManager& ECSEngine::getEventManager()
{
    return _eventManager;
}

} // namespace ECS
