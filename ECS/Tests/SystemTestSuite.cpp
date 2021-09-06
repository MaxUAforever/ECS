#include "SystemTestSuite.hpp"

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

struct GravityForce : public Component<GravityForce>
{
    explicit GravityForce(int value)
        : value{value}
    {};

    int value;
};

struct Weight : public Component<Weight>
{
    explicit Weight(int value)
        : value{value}
    {};

    int value;
};

struct EnginePower : public Component<EnginePower>
{
    explicit EnginePower(int value)
        : value{value}
    {};

    int value;
};

class SpaceShip : public Entity<SpaceShip>
{
};

class GravityPoint : public Entity<GravityPoint>
{
};

//std::string checkTypeIDGeneration()
//{
//
//
//    SpaceShip spaceship;
//
//
//    std::string result = "checkTypeIDGeneration: ";
//
//    auto success = true;
//
//    if (!isTypeIDForEqualTypesEques)
//    {
//        result += "[isTypeIDForEqualTypesEques] ";
//        success = false;
//    }
//    if (!isTypeIDForDifferentTypesNotEqual)
//    {
//        result += "[isTypeIDForDifferentTypesNotEqual] ";
//        success = false;
//    }
//    if (!isEntityIDDifferent)
//    {
//        result += "[isEntityIDDifferent] ";
//        success = false;
//    }
//
//    if (success)
//    {
//        result += "OK";
//    }
//
//    result += "\n";
//
//    return result;
//}

} // namespace

void SystemTests::runTests()
{
    
}

} // namespcae Tests
} // namespace ECS
