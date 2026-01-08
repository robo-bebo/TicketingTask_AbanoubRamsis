#pragma once
#include <chrono>
#include <cstdint>
#include <mutex>
#include <random>

class UniqueNumberGenerator
{
  private:
    std::mt19937_64                         rng; // 64-bit Mersenne Twister engine
    std::uniform_int_distribution<uint64_t> dist;
    std::mutex                              mtx; // thread-safe access

  public:
    // Constructor seeds the RNG using high-resolution clock
    UniqueNumberGenerator()
    {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        rng.seed(static_cast<uint64_t>(seed));
    }

    // Generates a random unique number (thread-safe)
    uint64_t getNext()
    {
        std::lock_guard<std::mutex> lock(mtx);
        return dist(rng);
    }
};
