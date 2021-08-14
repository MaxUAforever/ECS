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
        : _typeID(Utils::TypeIDGenerator<IEntity>::getID<Type>())
    {
    }
    
    TypeID getTypeID() const override
    {
        return _typeID;
    }
    
private:
    TypeID _typeID;
};

} // namespace ECS

#endif /* Entity_hpp */
