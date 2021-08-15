#ifndef Defs_hpp
#define Defs_hpp

#include <boost/uuid/uuid.hpp>

namespace ECS
{

using ComponentID = boost::uuids::uuid;
using EntityID = boost::uuids::uuid;
using TypeID = boost::uuids::uuid;

} // namespace ECS

#endif /* Defs_hpp */
