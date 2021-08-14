#ifndef IEntity_hpp
#define IEntity_hpp

#include "Utils/TypeIDGenerator.hpp"

namespace ECS
{

class IEntity
{
public:
    explicit IEntity()
        : _id(Utils::TypeIDGenerator<IEntity>::getEntityID())
    {
    }
    
    virtual ~IEntity() = default;
    
    virtual TypeID getTypeID() const = 0;
    
    inline EntityID getEntityID() const
    {
        return _id;
    };
    
private:
    EntityID _id;
};

} // namespace ECS

#endif /* IEntity_hpp */
