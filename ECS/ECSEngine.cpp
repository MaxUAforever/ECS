#include "ECSEngine.hpp"

namespace ECS
{

ECSEngine::ECSEngine()
    : _entityManager()
    , _systemManager()
    , _componentManager(std::make_unique<ComponentManager>(*_entityManager))
    , _eventManager(std::make_unique<EventManager>(*_systemManager))
{
}

EntityManager& ECSEngine::getEntityManager()
{
    return *_entityManager;
}

ComponentManager& ECSEngine::getComponentManager()
{
    return *_componentManager;
}

SystemManager& ECSEngine::getSystemManager()
{
    return *_systemManager;
}

EventManager& ECSEngine::getEventManager()
{
    return *_eventManager;
}

} // namespace ECS
