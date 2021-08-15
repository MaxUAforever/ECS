#include "EntityTestSuite.hpp"

#include "Entity.hpp"
#include "EntityManager.hpp"

#include "Component.hpp"
#include "ComponentManager.hpp"

#include <stdio.h>
#include <iostream>
#include <string>

namespace ECS
{
namespace Tests
{
namespace
{
struct A
{
};

struct B
{
};

class TestEntityA : public Entity<TestEntityA>
{
public:
    explicit TestEntityA(bool arg)
        : arg{arg}
    {
    };
    
    bool arg;
};

class TestComponentA : public Component<TestComponentA>
{
public:
    explicit TestComponentA(int value)
        : value{value}
    {
    };
    
    int value;
};

std::string checkTypeIDGeneration()
{
    Entity<A> entityA1;
    Entity<B> entityB;
    Entity<A> entityA2;
    
    const auto isTypeIDForEqualTypesEques = entityA1.getTypeID() == entityA2.getTypeID();
    const auto isTypeIDForDifferentTypesNotEqual = entityA1.getTypeID() != entityB.getTypeID();
    
    const auto isEntityIDDifferent = entityA1.getEntityID() != entityA2.getEntityID();
    
    std::string result = "checkTypeIDGeneration: ";
    
    auto success = true;
    
    if (!isTypeIDForEqualTypesEques)
    {
        result += "[isTypeIDForEqualTypesEques] ";
        success = false;
    }
    if (!isTypeIDForDifferentTypesNotEqual)
    {
        result += "[isTypeIDForDifferentTypesNotEqual] ";
        success = false;
    }
    if (!isEntityIDDifferent)
    {
        result += "[isEntityIDDifferent] ";
        success = false;
    }
    
    if (success)
    {
        result += "OK";
    }
    
    result += "\n";
    
    return result;
}

std::string checkEntityCreation()
{
    EntityManager entityManager;
    
    const auto& entityID1 = entityManager.createEntity<TestEntityA>(true);
    const auto& entityID2 = entityManager.createEntity<TestEntityA>(true);
    
    std::string result = "checkEntityCreation: ";
    result += (entityID1 == entityID2) ? "FAILED\n" : "OK\n";
    
    return result;
}

std::string checkEntityGet()
{
    EntityManager entityManager;
    
    const auto& entityID = entityManager.createEntity<TestEntityA>(true);
    auto* entity = entityManager.getEntity(entityID);
    
    std::string result = "checkEntityGet: ";
    result += (entity == nullptr) ? "FAILED\n" : "OK\n";
    
    return result;
}

std::string checkEntityRemove()
{
    EntityManager entityManager;
    
    const auto& entityID = entityManager.createEntity<TestEntityA>(true);
    entityManager.removeEntity(entityID);
    auto* entity = entityManager.getEntity(entityID);
    
    std::string result = "checkEntityGet: ";
    result += (entity == nullptr) ? "OK\n" : "FAILED\n";
    
    return result;
}

std::string checkComponentsAreRemovedWithEntity()
{
    EntityManager entityManager;
    ComponentManager componentsManager(entityManager);
    entityManager.registerObserver(&componentsManager);
    
    const auto& entityID = entityManager.createEntity<TestEntityA>(true);
    const auto& componentID = componentsManager.assignComponent<TestComponentA>(entityID, 100);
    
    std::string result = "checkComponentsAreRemovedWithEntity: ";
    
    auto* component = componentsManager.getComponent(componentID);
    if (component == nullptr)
    {
        result += "[failed assignComponent]\n";
        return result;
    }
    
    entityManager.removeEntity(entityID);
    
    component = componentsManager.getComponent(componentID);
    if (component != nullptr)
    {
        result += "[failed removeComponent]\n";
        return result;
    }
    
    result += "OK\n";
    return result;
}

std::string checkComponentsForEach()
{
    EntityManager entityManager;
    ComponentManager componentsManager(entityManager);
    entityManager.registerObserver(&componentsManager);
    
    const auto& entityID1 = entityManager.createEntity<TestEntityA>(true);
    const auto& componentID1 = componentsManager.assignComponent<TestComponentA>(entityID1, 100);
    
    const auto& entityID2 = entityManager.createEntity<TestEntityA>(false);
    const auto& componentID2 = componentsManager.assignComponent<TestComponentA>(entityID2, 50);
    
    std::string result = "checkComponentsForEach: ";
    
    componentsManager.forEach<TestComponentA>([](TestComponentA& a)
                                              {
                                                  a.value -= 20;
                                              });
    
    auto* component1Ptr = componentsManager.getComponent(componentID1);
    if (component1Ptr == nullptr)
    {
        result += "[failed assignComponent]\n";
        return result;
    }
    
    const auto& component1 = static_cast<TestComponentA&>(*component1Ptr);
    if (component1.value != 80)
    {
        result += "[Failed first ForEach]\n";
        return result;
    }
    
    auto* component2Ptr = componentsManager.getComponent(componentID2);
    if (component2Ptr == nullptr)
    {
        result += "[failed assignComponent]\n";
        return result;
    }
    
    const auto& component2 = static_cast<TestComponentA&>(*component2Ptr);
    if (component2.value != 30)
    {
        result += "[Failed second ForEach]\n";
        return result;
    }
    
    result += "OK\n";
    return result;
}

} // namespace

void EntityTests::runTests()
{
    std::cout << checkTypeIDGeneration();
    std::cout << checkEntityCreation();
    std::cout << checkEntityGet();
    std::cout << checkEntityRemove();
    std::cout << checkComponentsAreRemovedWithEntity();
    std::cout << checkComponentsForEach();
}

} // namespcae Tests
} // namespace ECS
