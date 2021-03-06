#ifndef ComponentManager_hpp
#define ComponentManager_hpp

#include "Defs.hpp"

#include "IComponent.hpp"
#include "Component.hpp"

#include "ECS/EntityDomain/IEntityManagerObserver.hpp"
#include "ECS/EntityDomain/EntityManager.hpp"

#include "ECS/Utils/UUIDHasher.hpp"
#include "ECS/Utils/TypeIDGenerator.hpp"

#include <cassert>
#include <unordered_map>
#include <unordered_set>

namespace ECS
{
using Components = std::unordered_map<ComponentID, std::unique_ptr<IComponent>, Utils::UUIDHasher>;

using EntityToComponentsMap = std::unordered_map<EntityID, std::unordered_map<TypeID, ComponentID, Utils::UUIDHasher>, Utils::UUIDHasher>;

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
        
        const auto componentID = component->getID();
        assert(_components.find(componentID) == _components.end());
        
        _entitiesMap[entityID].insert({component->getTypeID(), componentID});
        _components[componentID] = std::move(component);
        
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
    
    template <typename ConcreteComponent,
              typename = typename std::enable_if<std::is_base_of<IComponent, ConcreteComponent>::value>::type>
    ConcreteComponent* getComponent(const EntityID& entityID) const
    {
        if (_entityManager.getEntity(entityID) == nullptr)
        {
            return nullptr;
        }
        
        const auto& componentsMapIt = _entitiesMap.find(entityID);
        if (componentsMapIt == _entitiesMap.end())
        {
            return nullptr;
        }
        
        const auto& componentsMap = componentsMapIt->second;
        
        const auto typeID = Utils::TypeIDGenerator::getID<ConcreteComponent>();
        const auto& componentIt = componentsMap.find(typeID);
        if (componentIt == componentsMap.end())
        {
            return nullptr;
        }
        
        return static_cast<ConcreteComponent*>(_components.at(componentIt->second).get());
    }
    
    IComponent* getComponent(const ComponentID& id) const;
    
    void remove(const EntityID& entityID, const ComponentID& componentID);
    void clearEntity(const EntityID& entityID);
    void reset();
    
    void onEntityRemove(const EntityID& entityID) override;
    
public:
    using Iterator = typename Components::iterator;
    using ConstIterator = typename Components::const_iterator;
    
    Iterator begin()
    {
        return Iterator(_components.begin());
    }

    Iterator end()
    {
        return Iterator(_components.end());
    }

    ConstIterator begin() const
    {
        return ConstIterator(_components.cbegin());
    }

    ConstIterator end() const
    {
        return ConstIterator(_components.cend());
    }
    
private:
    const EntityManager& _entityManager;
    
private:
    Components _components;
    EntityToComponentsMap _entitiesMap;
};

} // namespace ECS

#endif /* ComponentManager_hpp */
