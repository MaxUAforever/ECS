#ifndef SystemManager_hpp
#define SystemManager_hpp

#include "ISystem.hpp"
#include "System.hpp"

#include "ECS/Defs.hpp"
#include "ECS/EventDomain/EventManager.hpp"
#include "ECS/Utils/UUIDHasher.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

namespace ECS
{
using SystemsContainer = std::unordered_map<SystemID, std::unique_ptr<ISystem>, Utils::UUIDHasher>;

class SystemManager
{
public:
    explicit SystemManager(const EventManager& eventManager);
    
    template <typename ConcreteSystem, typename... Args,
              typename = typename std::enable_if<std::is_base_of<ISystem, ConcreteSystem>::value>::type>
    EntityID addSystem(Args&&... args)
    {
        std::unique_ptr<ISystem> system = std::make_unique<ConcreteSystem>(ConcreteSystem(std::forward<Args>(args)...));
        
        const auto systemID = system->getID();
        _systems[systemID] = std::move(system);
        
        return systemID;
    }
    
    template <typename ConcreteSystem>
    ConcreteSystem* getSystem(const SystemID& id) const
    {
        return static_cast<ConcreteSystem*>(getSystem(id));
    }
    
    template <typename EventType>
    void registerEventObserver(const SystemID& id)
    {
        _eventManager.registerObserver<EventType>(getSystem(id));
    }
    
    ISystem* getSystem(const SystemID& id) const;
    void removeSystem(const SystemID& id);
    
    void updateSystems();
    
    void reset();
    
private:
    const EventManager& _eventManager;
    
    SystemsContainer _systems;
};

} // namespace ECS

#endif /* SystemManager_hpp */
