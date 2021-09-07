#include "EngineTestSuite.hpp"

#include "ECSEngine.hpp"

#include <stdio.h>
#include <iostream>
#include <string>

namespace ECS
{
namespace Tests
{
namespace
{

// Components

struct Health : public Component<Health>
{
    explicit Health(std::size_t value)
        : value{value}
    {};

    std::size_t value;
};

struct Position : public Component<Position>
{
    Position(int x, int y, int angle)
        : x{x}
        , y{y}
        , angle{angle}
    {};
    
    int x;
    int y;
    int angle;
};

struct Weight : public Component<Weight>
{
    explicit Weight(std::size_t value)
        : value{value}
    {};

    std::size_t value;
};

struct Engine : public Component<Engine>
{
    explicit Engine(std::size_t power)
        : power{power}
    {};

    std::size_t power;
};

struct GravityForce : public Component<GravityForce>
{
    explicit GravityForce(int value)
        : value{value}
    {};

    int value;
};

// Entities

class SpaceShip : public Entity<SpaceShip>
{
};

class BlackHole : public Entity<BlackHole>
{
};

// Events:

struct ColisionEvent : public Event<ColisionEvent>
{
    explicit ColisionEvent(const EntityID& firstEntityID, const EntityID& secondEntityID)
        : firstEntityID(firstEntityID)
        , secondEntityID(secondEntityID)
    {
    }
    
    EntityID firstEntityID;
    EntityID secondEntityID;
};

// Systems:

class CollisionSystem final : public System<CollisionSystem>
{
public:
    CollisionSystem(const EntityManager& entityManager,
                    const ComponentManager& componentManager,
                    const EventManager& eventManager)
        : _entityManager{entityManager}
        , _componentManager{componentManager}
        , _eventManager{eventManager}
    {
    }
    
    void update() override
    {
        for (auto firstIt = _entityManager.begin(); firstIt != _entityManager.end(); ++firstIt)
        {
            const auto& firstEntityID = firstIt->first;
            auto* firstPosition = _componentManager.getComponent<Position>(firstEntityID);
            
            if (firstPosition == nullptr)
            {
                continue;
            }
            
            for (auto secondIt = std::next(firstIt, 1); secondIt != _entityManager.end(); ++secondIt)
            {
                const auto& secondEntityID = secondIt->first;
                auto* secondPosition = _componentManager.getComponent<Position>(secondEntityID);
                
                if (secondPosition == nullptr)
                {
                    continue;
                }
                
                if (firstPosition->x == secondPosition->x && firstPosition->y == secondPosition->y)
                {
                    _eventManager.handleEvent(std::make_unique<ColisionEvent>(firstEntityID, secondEntityID));
                }
            }
        }
    }
    
private:
    const EntityManager& _entityManager;
    const ComponentManager& _componentManager;
    const EventManager& _eventManager;
};

class HealthSystem final : public System<HealthSystem>
{
public:
    HealthSystem(const ComponentManager& componentManager)
        : _componentManager{componentManager}
    {
    }
    
    void onEvent(IEvent* event) override
    {
        auto* colisionEvent = static_cast<ColisionEvent*>(event);
        if (colisionEvent == nullptr)
        {
            return;
        }
        
        const auto& firstEntityWeight =
            _componentManager.getComponent<Weight>(colisionEvent->firstEntityID);
        const auto& secondEntityWeight =
            _componentManager.getComponent<Weight>(colisionEvent->secondEntityID);
        
        if (firstEntityWeight == nullptr || secondEntityWeight == nullptr)
        {
            return;
        }
        
        auto* firstEntityHealth =
        _componentManager.getComponent<Health>(colisionEvent->firstEntityID);
        
        if (firstEntityHealth != nullptr)
        {
            if (secondEntityWeight->value > firstEntityHealth->value)
            {
                firstEntityHealth->value = 0;
            }
            else
            {
                firstEntityHealth->value -= secondEntityWeight->value;
            }
        }
        
        auto* secondEntityHealth =
        _componentManager.getComponent<Health>(colisionEvent->secondEntityID);
        
        if (secondEntityHealth != nullptr)
        {
            if (firstEntityWeight->value > secondEntityHealth->value)
            {
                secondEntityHealth->value = 0;
            }
            else
            {
                secondEntityHealth->value -= firstEntityWeight->value;
            }
        }
    }
    
private:
    const ComponentManager& _componentManager;
};

std::string checkECSEngineScenario()
{
    ECSEngine ecs;
    
    const auto& spaceShipEntityID = ecs.getEntityManager().createEntity<SpaceShip>();
    const auto& blackHoleEntityID = ecs.getEntityManager().createEntity<BlackHole>();

    ecs.getComponentManager().assignComponent<Health>(spaceShipEntityID, 100);
    ecs.getComponentManager().assignComponent<Position>(spaceShipEntityID, 0, 0, 0);
    ecs.getComponentManager().assignComponent<Weight>(spaceShipEntityID, 100);
    ecs.getComponentManager().assignComponent<Engine>(spaceShipEntityID, 10);
    
    ecs.getComponentManager().assignComponent<Position>(blackHoleEntityID, 0, 0, 0);
    ecs.getComponentManager().assignComponent<Weight>(blackHoleEntityID, 50);
    ecs.getComponentManager().assignComponent<GravityForce>(blackHoleEntityID, 5);
    
    ecs.getSystemManager().addSystem<CollisionSystem>(ecs.getEntityManager(),
                                                      ecs.getComponentManager(),
                                                      ecs.getEventManager());
    
    const auto& healthSystemID = ecs.getSystemManager().addSystem<HealthSystem>(ecs.getComponentManager());
    
    ecs.getEventManager().registerObserver<ColisionEvent>(healthSystemID);
    
    ecs.getSystemManager().updateSystems();
    
    auto* spaceShipHealth = ecs.getComponentManager().getComponent<Health>(spaceShipEntityID);
    
    std::string result = "checkECSEngineScenario: ";

    if (spaceShipHealth->value == 50)
    {
        result += "OK";
    }
    else
    {
        result += "FALSE";
    }

    result += "\n";

    return result;
}

} // namespace

void EngineTests::runTests()
{
    std::cout << checkECSEngineScenario();
}

} // namespcae Tests
} // namespace ECS
