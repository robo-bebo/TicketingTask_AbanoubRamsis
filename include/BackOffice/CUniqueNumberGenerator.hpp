#pragma once
#include <chrono>
#include <cstdint>
#include <mutex>
#include <random>

class UniqueNumberGenerator
{
  public:
    static uint64_t getNext()
    {
        auto&                       state = instance();
        std::lock_guard<std::mutex> lock(state.mtx);
        return state.dist(state.rng);
    }

  private:
    std::mt19937_64                         rng;
    std::uniform_int_distribution<uint64_t> dist;
    std::mutex                              mtx;

    UniqueNumberGenerator()
    {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        rng.seed(static_cast<uint64_t>(seed));
    }

    static UniqueNumberGenerator& instance()
    {
        static UniqueNumberGenerator inst;
        return inst;
    }
};
