#ifndef Timer_hpp
#define Timer_hpp

#include "ECS/Defs.hpp"

#include <chrono>

namespace ECS
{
namespace Utils
{

class Timer
{
public:
    inline static Time getCurrentTime()
    {
        return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    }
};

} // namespace Utils
} // namespace Hasher

#endif /* Timer_hpp */
