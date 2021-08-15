#ifndef IEntity_hpp
#define IEntity_hpp

#include "Utils/TypeIDGenerator.hpp"

namespace ECS
{

class IEntity
{
public:
    virtual ~IEntity() = default;
    
    virtual TypeID getTypeID() const = 0;
    virtual EntityID getEntityID() const = 0;
};

} // namespace ECS

#endif /* IEntity_hpp */
