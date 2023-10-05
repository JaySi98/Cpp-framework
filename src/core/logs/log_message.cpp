#include <core/logs/log_message.hpp>

namespace cpf::logs 
{
    log_message_data::log_message_data(
            std::filesystem::path file_,
            std::string function_,
            int line_,
            log_message_type type_,
            int thread_id
    ) : file(file_), function(function_), line(line_), type(type_), thread(thread_id), message("") 
    {
    }

    log_message::log_message(
        const char* file,
        const char* function,
        int line,
        log_message_type type,
        int thread_id
    ) : data(file, function, line, type, thread_id)
    {
    }

    log_message_data log_message::get_data() 
    {
        return data;
    }
        
    log_message& log_message::operator<<(std::string&& message)
    {
        // TODO
        // change to template function so that it is possible to add other types
        data.message = std::forward<std::string>(message);

        return *this;
    }
};