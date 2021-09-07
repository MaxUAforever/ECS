#ifndef ISystem_hpp
#define ISystem_hpp

#include "Defs.hpp"

#include "ECS/EventDomain/IEventManagerObserver.hpp"

#include <memory>

namespace ECS
{

class ISystem : public IEventManagerObserver
{
public:
    virtual ~ISystem() = default;
    
    virtual SystemID getID() const = 0;
    virtual TypeID getTypeID() const = 0;
    
    virtual void update() = 0;
};

} // namespace ECS

#endif /* ISystem_hpp */
