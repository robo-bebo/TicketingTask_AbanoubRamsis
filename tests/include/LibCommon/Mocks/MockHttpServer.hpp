#include "IHttpServer.hpp"

#include <gmock/gmock.h>

class MockHttpServer : public IHttpServer
{
  public:
    MOCK_METHOD(void, addRoute, (http::verb method, std::string path, Handler h), (override));
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
};