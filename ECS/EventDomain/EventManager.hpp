#ifndef EventManager_hpp
#define EventManager_hpp

#include "IEvent.hpp"
#include "IEventManagerObserver.hpp"
#include "Event.hpp"

#include "ECS/Defs.hpp"
#include "ECS/Utils/TypeIDGenerator.hpp"
#include "ECS/Utils/UUIDHasher.hpp"

#include <unordered_map>
#include <vector>

namespace ECS
{
using EventTypeObservers = std::unordered_map<TypeID, std::vector<IEventManagerObserver*>, Utils::UUIDHasher>;

class EventManager
{
public:
    template <typename ConcreteEvent, typename... Args,
              typename = typename std::enable_if<std::is_base_of<IEvent, ConcreteEvent>::value>::type>
    void handleEvent(Args&&... args)
    {
        ConcreteEvent event{std::forward<Args>(args)...};
        
        const auto eventTypeID = event.getTypeID();
        
        const auto typeObserversIt = _observers.find(eventTypeID);
        if (typeObserversIt == _observers.end())
        {
            return;
        }
        
        const auto& typeObservers = typeObserversIt->second;
        for (auto* typeObserver : typeObservers)
        {
            typeObserver->onEvent(&event);
        }
    }

    template <typename EventType>
    void registerObserver(IEventManagerObserver* observer)
    {
        const auto typeID = Utils::TypeIDGenerator::getID<EventType>();
        _observers[typeID].push_back(observer);
    }
    
private:
    EventTypeObservers _observers;
};

} // namespace ECS

#endif /* EventManager_hpp */
