#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class DateTime
{
  private:
    std::chrono::system_clock::time_point tp;

  public:
    // Default constructor: current time
    DateTime() : tp(std::chrono::system_clock::now()) {}

    // Constructor from time_point
    explicit DateTime(const std::chrono::system_clock::time_point& t) : tp(t) {}

    // Convert Time to string "YYYY-MM-DD HH:MM:SS"
    std::string toString() const
    {
        std::time_t        t_c = std::chrono::system_clock::to_time_t(tp);
        std::tm            tm  = *std::localtime(&t_c);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    // Create DateTime from string "YYYY-MM-DD HH:MM:SS"
    static DateTime fromString(const std::string& str)
    {
        std::tm            tm = {};
        std::istringstream iss(str);
        iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        if(iss.fail())
        {
            throw std::runtime_error("Failed to parse time string");
        }
        auto time_c = std::mktime(&tm);
        return DateTime(std::chrono::system_clock::from_time_t(time_c));
    }

    // Access underlying time_point (optional)
    std::chrono::system_clock::time_point getTimePoint() const { return tp; }
};
