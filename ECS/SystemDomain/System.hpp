#ifndef System_hpp
#define System_hpp

#include "ISystem.hpp"

#include "ECS/Utils/TypeIDGenerator.hpp"

namespace ECS
{

template <typename Type>
class System : public ISystem
{
public:
    System()
        : _id(Utils::SystemIDGenerator::getSystemID())
        , _typeID(Utils::TypeIDGenerator::getID<Type>())
    {
    }
    
    SystemID getID() const override
    {
        return _id;
    }
    
    TypeID getTypeID() const override
    {
        return _typeID;
    }
    
    void update() override
    {
    }
    
    void onEvent(IEvent* event) override
    {
    }
    
private:
    EntityID _id;
    TypeID _typeID;
};

} // namespace ECS

#endif /* System_hpp */
