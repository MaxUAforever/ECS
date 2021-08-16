#ifndef IEntityManagerObserver_hpp
#define IEntityManagerObserver_hpp

#include "Defs.hpp"

namespace ECS
{

class IEntityManagerObserver
{
public:
    virtual ~IEntityManagerObserver() = default;
    
    virtual void onEntityRemove(const EntityID& entityID) = 0;
};

} // namespace ECS

#endif /* IEntityManagerObserver_hpp */
