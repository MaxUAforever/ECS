#ifndef IComponent_hpp
#define IComponent_hpp

#include "Defs.hpp"

namespace ECS
{

class ISystem
{
public:
    virtual ~ISystem() = default;
    
    virtual SystemID getID() const = 0;
    virtual TypeID getTypeID() const = 0;
};

} // namespace ECS

#endif /* IComponent_hpp */
