#include <iostream>

#include "ECS/Tests/EntityTestSuite.hpp"
#include "ECS/Tests/EventTestSuite.hpp"

int main(int argc, const char * argv[])
{
    ECS::Tests::EntityTests::runTests();
    ECS::Tests::EventTests::runTests();
    
    return 0;
}
