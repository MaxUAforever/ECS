#include <iostream>

#include "ECS/Tests/EntityTestSuite.hpp"
#include "ECS/Tests/EngineTestSuite.hpp"

int main(int argc, const char * argv[])
{
    ECS::Tests::EntityTests::runTests();
    ECS::Tests::EngineTests::runTests();
    
    return 0;
}
