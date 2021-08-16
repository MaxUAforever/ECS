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
using EventsContainer = std::unordered_map<EventID, std::unique_ptr<IEvent>, Utils::UUIDHasher>;
using EventTypesMap = std::unordered_map<TypeID, std::vector<EventID>, Utils::UUIDHasher>;

using EventTypeObservers = std::unordered_map<TypeID, std::vector<IEventManagerObserver*>, Utils::UUIDHasher>;

class EventManager
{
public:
    template <typename ConcreteEvent, typename... Args,
              typename = typename std::enable_if<std::is_base_of<IEvent, ConcreteEvent>::value>::type>
    EventID addEvent(Args&&... args)
    {
        std::unique_ptr<IEvent> event = std::make_unique<ConcreteEvent>(ConcreteEvent(std::forward<Args>(args)...));
        
        const auto eventID = event->getID();
        const auto typeID = event->getTypeID();
        
        _eventsBuffer[eventID] = std::move(event);
        _eventTypesMap[typeID].push_back(eventID);
        
        return eventID;
    }

    template <typename EventType>
    void registerObserver(IEventManagerObserver* observer)
    {
        const auto typeID = Utils::TypeIDGenerator::getID<EventType>();
        _observers[typeID].push_back(observer);
    }
    
    void reset();
    void sendEvents();
    
private:
    EventsContainer _eventsBuffer;
    EventTypesMap _eventTypesMap;
    
    EventTypeObservers _observers;
};

} // namespace ECS

#endif /* EventManager_hpp */
