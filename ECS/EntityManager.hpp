#ifndef EntityManager_hpp
#define EntityManager_hpp

#include "IEntity.hpp"
#include "IEntityManagerObserver.hpp"

#include "Utils/TypeIDGenerator.hpp"
#include "Utils/UUIDHasher.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

namespace ECS
{
using EntitiesContainer = std::unordered_map<EntityID, std::unique_ptr<IEntity>, Utils::UUIDHasher>;

class EntityManager
{
public:
    template <typename ConcreteEntity, typename... Args,
              typename = typename std::enable_if<std::is_base_of<IEntity, ConcreteEntity>::value>::type>
    EntityID createEntity(Args&&... args)
    {
        std::unique_ptr<IEntity> entity = std::make_unique<ConcreteEntity>(ConcreteEntity(std::forward<Args>(args)...));
        
        const auto entityID = entity->getEntityID();
        _entitiesContainer[entityID] = std::move(entity);
        
        return entityID;
    }
    
    IEntity* getEntity(const EntityID& id) const
    {
        auto entityIt = _entitiesContainer.find(id);
        
        if (entityIt == _entitiesContainer.end())
        {
            return nullptr;
        }
        
        return entityIt->second.get();
    }
    
    void reset()
    {
        _entitiesContainer.clear();
    }
    
    void removeEntity(const EntityID& id)
    {
        _entitiesContainer.erase(id);
        notifyIsRemoved(id);
    }
    
    void notifyIsRemoved(const EntityID& id)
    {
        for (auto observer : _observers)
        {
            observer->onEntityRemove(id);
        }
    }
    
    void registerObserver(IEntityManagerObserver* observer)
    {
        _observers.push_back(observer);
    }
    
private:
    EntitiesContainer _entitiesContainer;
    
    std::vector<IEntityManagerObserver*> _observers;
};

} // namespace ECS

#endif /* EntityManager_hpp */
