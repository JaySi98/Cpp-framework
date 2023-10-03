#include <core/logs/log_message.hpp>

namespace cpf::logs 
{
    log_message_data::log_message_data(
            const char* file_,
            const char* function_,
            int line_,
            std::string text_,
            log_message_type type_
    ) //: path(file_), function(function_), line(line_), text(text_), type(type_) 
    {}

    log_message::log_message(
        const char* file,
        const char* function,
        int line,
        std::string text,
        log_message_type type,
        unsigned long thread_id
    ) : data(file, function, line, text, type)
    {}

    log_message_data log_message::get_data() 
    {
        return data;
    }
};