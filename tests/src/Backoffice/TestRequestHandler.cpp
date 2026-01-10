#include "Backoffice/Mocks/MockReportsDatabase.hpp"
#include "Backoffice/Mocks/MockTicketStockDatabase.hpp"
#include "CRequestHandler.hpp"
#include "Types/CTicketValidationResponse.hpp"

#include <gtest/gtest.h>
#include <memory>

class RequestHandlerTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        auto reportDb = std::make_unique<IReportsDatabaseMock>();
        auto ticketDb = std::make_unique<ITicketStockDatabaseMock>();

        m_reportDatabase = reportDb.get(); // raw alias
        m_ticketDatabase = ticketDb.get(); // raw alias

        m_requestHandler = std::make_unique<RequestHandler>(std::move(ticketDb), std::move(reportDb));
    }

    IReportsDatabaseMock*           m_reportDatabase; // RAW pointer (non-owning)
    ITicketStockDatabaseMock*       m_ticketDatabase; // RAW pointer (non-owning)
    std::unique_ptr<RequestHandler> m_requestHandler;
};

TEST_F(RequestHandlerTest, ValidationRequest)
{
    Request req;
    req.body() = "eyJWYWxpZGl0eURheXMiOjMwLCJjcmVhdGlvbkRhdGUiOiIyMDI2LTAxLTEwIDIzOjAyOjUxIiwibGluZ"
                 "U51bWJlciI6NSwidGlja2V0SUQiOjE1NzkxNTc5NzA3MzE3NjI2ODc5fQ==";

    EXPECT_CALL(*m_ticketDatabase, isTicketOnDatabase(req.body())).WillOnce(::testing::Return(true));

    auto response = m_requestHandler->ticketValidationRequestHandler(req);

    TicketValidationResponse validationResponse;
    validationResponse.valid = true;
    ;

    Response ExpectedRes{http::status::ok, req.version()};
    ExpectedRes.body() = validationResponse.toString();


    EXPECT_EQ(response.body(), ExpectedRes.body());
}