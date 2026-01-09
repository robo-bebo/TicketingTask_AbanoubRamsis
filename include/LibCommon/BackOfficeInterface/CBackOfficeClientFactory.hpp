#pragma once

#include "BackOfficeInterface/CBackOfficeHttpClient.hpp"

class BackOfficeClientFactory
{
  public:
    static inline std::unique_ptr<IBackOfficeClient> createHttpClient()
    {
        return std::make_unique<CBackOfficeHttpClient>();
    }
};