#ifndef EventManager_hpp
#define EventManager_hpp

#include "IEvent.hpp"
#include "IEventManagerObserver.hpp"
#include "Event.hpp"

#include "ECS/Defs.hpp"
#include "ECS/SystemDomain/SystemManager.hpp"
#include "ECS/Utils/TypeIDGenerator.hpp"
#include "ECS/Utils/UUIDHasher.hpp"

#include <unordered_map>
#include <vector>

namespace ECS
{
using EventTypeObservers = std::unordered_map<TypeID, std::vector<IEventManagerObserver*>, Utils::UUIDHasher>;
using EventFunction = std::function<void(IEvent*)>;

class EventManager
{
public:
    explicit EventManager(const SystemManager& systemManager);
    
    void handleEvent(std::unique_ptr<IEvent> event) const;

    template <typename EventType>
    void registerObserver(const SystemID& id)
    {
        const auto typeID = Utils::TypeIDGenerator::getID<EventType>();
        _observers[typeID].push_back(_systemManager.getSystem(id));
    }
    
private:
    const SystemManager& _systemManager;
    
    EventTypeObservers _observers;
};

} // namespace ECS

#endif /* EventManager_hpp */
