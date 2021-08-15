#include <iostream>

#include "IComponent.hpp"
#include "EntityManager.hpp"
#include "Tests/EntityTestSuite.hpp"

int main(int argc, const char * argv[])
{
    ECS::Tests::EntityTests::runTests();
    
    return 0;
}
