#ifndef Entity_hpp
#define Entity_hpp

#include "IEntity.hpp"
#include "Utils/TypeIDGenerator.hpp"

namespace ECS
{

template <typename Type>
class Entity : public IEntity
{
public:
    Entity()
        : _id(Utils::EntityIDGenerator::getEntityID())
        , _typeID(Utils::TypeIDGenerator::getID<Type>())
    {
    }
    
    EntityID getEntityID() const override
    {
        return _id;
    };
    
    TypeID getTypeID() const override
    {
        return _typeID;
    }
    
private:
    EntityID _id;
    TypeID _typeID;
};

} // namespace ECS

#endif /* Entity_hpp */
