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
    void handleEvent(std::unique_ptr<IEvent> event) const;

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
