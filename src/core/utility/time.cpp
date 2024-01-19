#include <core/utility/time.hpp>
#include <iomanip>

namespace cpf::utility
{
    std::string current_time_as_str(const std::string& format)
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        
        std::ostringstream stream{};
        stream << std::put_time(&tm, format.c_str());
        
        return stream.str();
    }
};