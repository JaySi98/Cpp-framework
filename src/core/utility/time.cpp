#include <core/utility/time.hpp>
#include <iomanip>

namespace cpf::utility
{
    std::ostringstream current_time_as_stream(const char* format)
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        
        std::ostringstream stream{};
        stream << std::put_time(&tm, format);
        
        return stream;
    }
};