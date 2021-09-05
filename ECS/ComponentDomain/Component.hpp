#ifndef Component_hpp
#define Component_hpp

#include "IComponent.hpp"

#include "ECS/Utils/TypeIDGenerator.hpp"

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
    
private:
    ComponentID _id;
    TypeID _typeID;
};

} // namespace ECS

#endif /* Component_hpp */
