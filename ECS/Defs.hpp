#ifndef Defs_hpp
#define Defs_hpp

#include <boost/uuid/uuid.hpp>

#include <time.h>

namespace ECS
{

using ComponentID = boost::uuids::uuid;
using EntityID = boost::uuids::uuid;
using EventID = boost::uuids::uuid;
using TypeID = boost::uuids::uuid;

using Time = time_t;

} // namespace ECS

#endif /* Defs_hpp */
