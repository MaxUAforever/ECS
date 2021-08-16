#ifndef EntityManager_hpp
#define EntityManager_hpp

#include "IEntity.hpp"
#include "IEntityManagerObserver.hpp"
#include "Entity.hpp"

#include "ECS/Utils/TypeIDGenerator.hpp"
#include "ECS/Utils/UUIDHasher.hpp"

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
    
    template <typename ConcreteEntity>
    ConcreteEntity* getEntity(const EntityID& id) const
    {
        return static_cast<ConcreteEntity*>(getEntity(id));
    }
    
    IEntity* getEntity(const EntityID& id) const;
    
    void reset();
    
    void removeEntity(const EntityID& id);
    void notifyIsRemoved(const EntityID& id);

    void registerObserver(IEntityManagerObserver* observer);
    
private:
    EntitiesContainer _entitiesContainer;
    
    std::vector<IEntityManagerObserver*> _observers;
};

} // namespace ECS

#endif /* EntityManager_hpp */
