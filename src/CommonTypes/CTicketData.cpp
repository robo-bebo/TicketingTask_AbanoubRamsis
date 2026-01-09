#include "CommonTypes/CTicketData.hpp"

std::string TicketData::toBase64() const
{
    const nlohmann::json json       = *this;
    const std::string    jsonString = json.dump();
    std::string          base64Str;
    base64Str.resize(boost::beast::detail::base64::encoded_size(jsonString.length()));
    boost::beast::detail::base64::encode(reinterpret_cast<void*>(&base64Str[0]), jsonString.c_str(),
                                         jsonString.length());
    return base64Str;
}


TicketData TicketData::fromBase64(const std::string& base64Str)
{
    std::string decodedJson;
    decodedJson.resize(boost::beast::detail::base64::decoded_size(base64Str.length()));
    boost::beast::detail::base64::decode(reinterpret_cast<void*>(&decodedJson[0]),
                                         base64Str.c_str(), base64Str.length());
    nlohmann::json json = nlohmann::json::parse(decodedJson);
    return json.get<TicketData>();
}

void from_json(const nlohmann::json& json, TicketData& data)
{
    data.ticketID     = json.at("ticketID").get<uint64_t>();
    data.ValidityDays = json.at("ValidityDays").get<int32_t>();
    data.lineNumber   = json.at("lineNumber").get<int8_t>();
    data.creationDate = DateTime::fromString(json.at("creationDate").get<std::string>());
}

void to_json(nlohmann::json& json, const TicketData& data)
{

    json["ticketID"]     = data.ticketID;
    json["ValidityDays"] = data.ValidityDays;
    json["lineNumber"]   = data.lineNumber;
    json["creationDate"] = data.creationDate.toString();
}
