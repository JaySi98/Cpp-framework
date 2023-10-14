#include <core/logs/log_data.hpp>
#include <core/utility/type_literal_map.hpp>

namespace cpf::logs 
{
    static constexpr std::array<std::pair<log_type, std::string_view>, 6> literals
    {{
        {log_type::hint,          "HINT"},
        {log_type::information,   "INFO"},
        {log_type::warning,       "WARN"},
        {log_type::caution,       "CAUTION"},
        {log_type::error,         "ERROR"},
        {log_type::fatal,         "FATAL"}
    }};

    const std::string_view log_type_literal(log_type type)
    {
        static constexpr auto map = 
            utility::type_literal_map<log_type, std::string_view, literals.size()>{{literals}};

        return map.at(type);
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