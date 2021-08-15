#ifndef Component_hpp
#define Component_hpp

#include "IComponent.hpp"

#include "Utils/TypeIDGenerator.hpp"

namespace ECS
{

template <typename Type>
class Component : public IComponent
{
public:
    Component()
        : _id(Utils::ComponentIDGenerator::getComponentID())
        , _typeID(Utils::TypeIDGenerator::getID<Type>())
    {
    }
    
    ComponentID getID() const override
    {
        return _id;
    }
    
    TypeID getTypeID() const override
    {
        return _typeID;
    }
    
    EntityID getOwnerID() const override
    {
        return _ownerID;
    };
    
    void assign(const EntityID& entityID) override
    {
        _ownerID = entityID;
    }
    
private:
    ComponentID _id;
    TypeID _typeID;
    EntityID _ownerID;
};

} // namespace ECS

#endif /* Component_hpp */
