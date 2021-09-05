#ifndef Event_hpp
#define Event_hpp

#include "IEvent.hpp"

#include "ECS/Utils/Timer.hpp"
#include "ECS/Utils/TypeIDGenerator.hpp"

namespace ECS
{

template <typename Type>
class Event : public IEvent
{
public:
    Event()
        : _id(Utils::EventIDGenerator::getEventID())
        , _typeID(Utils::TypeIDGenerator::getID<Type>())
    {
    }
    
    inline EventID getID() const override
    {
        return _id;
    };
    
    inline TypeID getTypeID() const override
    {
        return _typeID;
    }
    
private:
    EventID _id;
    TypeID _typeID;
};

} // namespace ECS

#endif /* Event_hpp */
