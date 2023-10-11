#include <core/logs/log_data.hpp>

namespace cpf::logs 
{
    log_data::log_data(
        std::filesystem::path file_,
        std::string function_,
        int line_,
        log_type type_,
        int thread_id
    ) : file(file_), function(function_), line(line_), type(type_), thread(thread_id), message("") 
    {}   
};