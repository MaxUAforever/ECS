#ifndef ComponentManager_hpp
#define ComponentManager_hpp

#include "Defs.hpp"
#include "IComponent.hpp"
#include "IEntityManagerObserver.hpp"

#include "EntityManager.hpp"

#include "Utils/UUIDHasher.hpp"
#include "Utils/TypeIDGenerator.hpp"

#include <cassert>
#include <unordered_map>
#include <unordered_set>

namespace ECS
{
using Components = std::unordered_map<ComponentID, std::unique_ptr<IComponent>, Utils::UUIDHasher>;
using EntityToComponentsMap = std::unordered_map<EntityID, std::unordered_set<ComponentID, Utils::UUIDHasher>, Utils::UUIDHasher>;

class ComponentManager : public IEntityManagerObserver
{
public:
    explicit ComponentManager(const EntityManager& entityManager)
        : _entityManager{entityManager}
    {
    }
    
    /**
     * Function 'assignComponent' allows to create and add a component to
     * any existing entity.
     *
     * It checks if an entity exists by the passed id and construct object
     * of 'ConcreteComponent' type, that must be a devired type of
     * 'IComponent'. Then component will be created and assigned to entity.
     *
     * @tparam ConcreteComponent is the type of created component. It must
     *         be a devired type of IComponent
     * @tparam Args is a variadic type of arguments for creating
     *              ConcreteComponent.
     *
     * @param entityID is an id of the entity to which the component
     *        will be assigned.
     * @param args is a set of arguments for creating ConcreteComponent.
     *
     * @return ComponentID of created component.
     */
    template <typename ConcreteComponent, typename... Args,
              typename = typename std::enable_if<std::is_base_of<IComponent, ConcreteComponent>::value>::type>
    ComponentID assignComponent(const EntityID& entityID, Args&&... args)
    {
        if (_entityManager.getEntity(entityID) == nullptr)
        {
            return ComponentID{};
        }
        
        std::unique_ptr<IComponent> component = std::make_unique<ConcreteComponent>(ConcreteComponent(std::forward<Args>(args)...));
        
        component->assign(entityID);
        
        const auto componentID = component->getID();
        assert(_components.find(componentID) == _components.end());
        
        _components[componentID] = std::move(component);
        _entitiesMap[entityID].insert(componentID);
        
        return componentID;
    }
    
    template <typename Type, typename Function,
              typename = typename std::enable_if<std::is_base_of<IComponent, Type>::value>::type>
    void forEach(Function function)
    {
        const auto typeID = Utils::TypeIDGenerator::getID<Type>();
        
        for (auto& componentValue : _components)
        {
            auto& component = *componentValue.second;
            
            if (component.getTypeID() == typeID)
            {
                function(static_cast<Type&>(component));
            }
        }
    }
    
    IComponent* getComponent(const ComponentID& id) const;
    
    void remove(const EntityID& entityID, const ComponentID& componentID);
    void clearEntity(const EntityID& entityID);
    void reset();
    
    void onEntityRemove(const EntityID& entityID) override;
    
private:
    const EntityManager& _entityManager;
    
private:
    Components _components;
    EntityToComponentsMap _entitiesMap;
};

} // namespace ECS

#endif /* ComponentManager_hpp */
