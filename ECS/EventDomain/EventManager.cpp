#include "EventManager.hpp"

namespace ECS
{

void EventManager::reset()
{
    _eventsBuffer.clear();
    _eventTypesMap.clear();
}

void EventManager::sendEvents()
{
    for (const auto& eventValue : _eventTypesMap)
    {
        const auto& eventTypeID = eventValue.first;
        const auto& eventIDs = eventValue.second;
        
        const auto typeObserversIt = _observers.find(eventTypeID);
        if (typeObserversIt == _observers.end())
        {
            continue;
        }
        
        const auto& typeObservers = typeObserversIt->second;
        for (auto* typeObserver : typeObservers)
        {
            for (const auto& eventID : eventIDs)
            {
                typeObserver->onEvent(_eventsBuffer.at(eventID).get());
            }
        }
    }
    
    reset();
}

} // namespace ECS
