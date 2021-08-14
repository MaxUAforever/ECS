#include "UUIDHasher.hpp"

#include <boost/functional/hash.hpp>

namespace ECS
{
namespace Utils
{

size_t UUIDHasher::operator()(const boost::uuids::uuid& uuid) const
{
    return boost::hash<boost::uuids::uuid>()(uuid);
}

} // namespace Utils
} // namespace Hasher
