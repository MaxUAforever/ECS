#ifndef IEventManagerObserver_hpp
#define IEventManagerObserver_hpp

#include "IEvent.hpp"

namespace ECS
{

class IEventManagerObserver
{
public:
    virtual ~IEventManagerObserver() = default;
    
    virtual void onEvent(IEvent* event) = 0;
};

} // namespace ECS

#endif /* IEventManagerObserver_hpp */
