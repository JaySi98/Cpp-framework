#include <core/logs/log_data.hpp>
#include <map>

namespace cpf::logs 
{

    const std::string_view log_type_literal(log_type type)
    {
        static std::map<log_type, const char*> map
        {
            {log_type::hint,          "HINT"},
            {log_type::information,   "INFO"},
            {log_type::warning,       "WARN"},
            {log_type::caution,       "CAUTION"},
            {log_type::error,         "ERROR"},
            {log_type::fatal,         "FATAL"}
        };

        return std::string_view{map[type]};
    }

    log_data::log_data(
        const std::filesystem::path& file_,
        const std::string& function_,
        int line_,
        log_type type_,
        int thread_id
    ) : file(file_), function(function_), line(line_), type(type_), thread(thread_id), message() 
    {}   
};