#ifndef IComponent_hpp
#define IComponent_hpp

#include "Defs.hpp"

namespace ECS
{

class IComponent
{
public:
    virtual ~IComponent() = default;
    
    virtual ComponentID getID() const = 0;
    virtual TypeID getTypeID() const = 0;
    virtual EntityID getOwnerID() const = 0;
    virtual void assign(const EntityID& entityID) = 0;
};

} // namespace ECS

#endif /* IComponent_hpp */
