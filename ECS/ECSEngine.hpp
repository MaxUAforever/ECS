#ifndef ECSEngine_hpp
#define ECSEngine_hpp

#include "ECS/EventDomain/EventManager.hpp"
#include "ECS/EntityDomain/EntityManager.hpp"
#include "ECS/ComponentDomain/ComponentManager.hpp"
#include "ECS/SystemDomain/SystemManager.hpp"

#include <memory>

namespace ECS
{

class ECSEngine
{
public:
    ECSEngine();
    
    EntityManager& getEntityManager();
    ComponentManager& getComponentManager();
    SystemManager& getSystemManager();
    EventManager& getEventManager();
    
private:
    EntityManager _entityManager;
    ComponentManager _componentManager;
    SystemManager _systemManager;
    EventManager _eventManager;
};

} // namespace ECS

#endif /* ECSEngine_hpp */
