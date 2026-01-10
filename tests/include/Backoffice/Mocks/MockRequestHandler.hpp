#pragma once

#include "IRequestHandler.hpp"

#include <gmock/gmock.h>

class MockRequestHandler : public IRequestHandler
{
  public:
    MOCK_METHOD(Response, ticketSaleRequestHandler, (const Request& req), (override));
    MOCK_METHOD(Response, ticketValidationRequestHandler, (const Request& req), (override));
    MOCK_METHOD(Response, postTransactionReportHandler, (const Request& req), (override));
    MOCK_METHOD(Response, getTransactionReportHandler, (const Request& req), (override));
};