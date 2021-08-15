#ifndef TypeIDGenerator_hpp
#define TypeIDGenerator_hpp

#include <boost/uuid/uuid_generators.hpp>

#include "../Defs.hpp"

namespace ECS
{
namespace Utils
{

class TypeIDGenerator
{
public:
    template <typename Type>
    inline static TypeID getID()
    {
        static TypeID typeID = boost::uuids::random_generator()();
        return typeID;
    }
};

class EntityIDGenerator
{
public:
    inline static EntityID getEntityID()
    {
        return boost::uuids::random_generator()();
    }
};

class ComponentIDGenerator
{
public:
    inline static EntityID getComponentID()
    {
        return boost::uuids::random_generator()();
    }
};

} // namespace Utils
} // namespace ECS

#endif /* TypeIDGenerator_hpp */
