#include "EventManager.hpp"

namespace ECS
{

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
