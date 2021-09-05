#include "EventTestSuite.hpp"

#include "ECS/EventDomain/EventManager.hpp"
#include "ECS/EventDomain/IEventManagerObserver.hpp"

#include "ECS/ComponentDomain/ComponentManager.hpp"

#include "ECS/EntityDomain/EntityManager.hpp"

#include <stdio.h>
#include <iostream>
#include <string>

namespace ECS
{
namespace Tests
{

namespace
{

struct LifeComponent : Component<LifeComponent>
{
    explicit LifeComponent(bool isAlive)
        : isAlive(isAlive)
    {
    }
    
    bool isAlive;
};

struct LifeEntity : Entity<LifeEntity>
{
};

struct EntityKilledTestEvent : public Event<EntityKilledTestEvent>
{
    explicit EntityKilledTestEvent(const EntityID& entityID)
        : entityID(entityID)
    {
    }
    
    EntityID entityID;
};

class TestEventObserver : public IEventManagerObserver
{
public:
    TestEventObserver(const ComponentManager& componentManager)
        : _componentManager(componentManager)
    {
    }
    
    void onEvent(IEvent* event) override
    {
        auto* killedEvent = static_cast<EntityKilledTestEvent*>(event);
        
        const auto entityID = killedEvent->entityID;
        
        auto* lifeComponent = _componentManager.getComponent<LifeComponent>(entityID);
        if (lifeComponent == nullptr)
        {
            return;
        }
        
        lifeComponent->isAlive = false;
    }
    
private:
    const ComponentManager& _componentManager;
};

std::string checkEventObserver()
{
    EntityManager entityManager;
    ComponentManager componentManager(entityManager);
    EventManager eventManager;
    
    TestEventObserver testEventObserver(componentManager);
    
    entityManager.registerObserver(&componentManager);
    eventManager.registerObserver<EntityKilledTestEvent>(&testEventObserver);
    
    const auto& entityID = entityManager.createEntity<LifeEntity>();
    componentManager.assignComponent<LifeComponent>(entityID, true);
    
    eventManager.handleEvent<EntityKilledTestEvent>(entityID);
    
    auto* lifeComponent = componentManager.getComponent<LifeComponent>(entityID);
    
    std::string result = "checkEventObserver: ";
    if (lifeComponent == nullptr)
    {
        result += "[Failed component assign]\n";
        return result;
    }
    
    if (lifeComponent->isAlive != false)
    {
        result += "[Failed event]\n";
        return result;
    }
    
    result += "OK\n";
    
    return result;
}

} // namespace

void EventTests::runTests()
{
    std::cout << checkEventObserver();
}

} // namespace Tests
} // namespace ECS
