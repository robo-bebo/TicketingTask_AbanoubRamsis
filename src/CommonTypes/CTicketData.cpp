#include "CommonTypes/CTicketData.hpp"


std::string TicketData::toBase64() const
{
    nlohmann::json json;
    from_json(json, *this);
    std::string jsonString = json.dump();
    std::string base64Str;
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