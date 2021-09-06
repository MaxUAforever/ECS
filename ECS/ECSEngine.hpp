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
    
private:
    std::unique_ptr<EventManager> _eventManager;
    std::unique_ptr<EntityManager> _entityManager;
    std::unique_ptr<ComponentManager> _componentManager;
    std::unique_ptr<SystemManager> _systemManager;
};

} // namespace ECS

#endif /* ECSEngine_hpp */
