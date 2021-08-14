#ifndef UUIDHasher_hpp
#define UUIDHasher_hpp

#include <boost/uuid/uuid.hpp>

namespace ECS
{
namespace Utils
{

struct UUIDHasher
{
    size_t operator()(const boost::uuids::uuid& uuid) const;
};

} // namespace Utils
} // namespace Hasher

#endif /* UUIDHasher_hpp */
