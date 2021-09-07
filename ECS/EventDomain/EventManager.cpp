#include "EventManager.hpp"

namespace ECS
{
EventManager::EventManager(const SystemManager& systemManager)
    : _systemManager{systemManager}
{
}

void EventManager::handleEvent(std::unique_ptr<IEvent> event) const
{
    const auto eventTypeID = event->getTypeID();
    
    const auto typeObserversIt = _observers.find(eventTypeID);
    if (typeObserversIt == _observers.end())
    {
        return;
    }
    
    const auto& typeObservers = typeObserversIt->second;
    for (auto* typeObserver : typeObservers)
    {
        typeObserver->onEvent(event.get());
    }
}

} // namespace ECS
