#include "ECSEngine.hpp"

namespace ECS
{

ECSEngine::ECSEngine()
    : _eventManager()
    , _entityManager()
    , _componentManager(std::make_unique<ComponentManager>(*_entityManager))
    , _systemManager(std::make_unique<SystemManager>(*_eventManager))
{
}

EntityManager& ECSEngine::getEntityManager()
{
    return *_entityManager;
}


} // namespace ECS
