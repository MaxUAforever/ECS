#ifndef IEvent_hpp
#define IEvent_hpp

#include "ECS/Defs.hpp"

namespace ECS
{

class IEvent
{
public:
    virtual ~IEvent() = default;
    
    virtual TypeID getTypeID() const = 0;
    virtual EventID getID() const = 0;
    
    virtual Time getCreationTime() const = 0;
};

} // namespace ECS

#endif /* IEvent_hpp */
