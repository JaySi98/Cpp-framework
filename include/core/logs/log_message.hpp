#pragma once

#include <string>
#include <filesystem>
#include <sstream>

namespace cpf::logs 
{
    enum class log_message_type
    {
        hint,
        information,
        warning,
        caution,
        error,
        fatal
    };

    struct log_message_data 
    {
        explicit log_message_data(
            std::filesystem::path file_,
            std::string function_,
            int line_,
            log_message_type type_,
            int thread_id
        );
    
        std::filesystem::path file{};
        std::string function{};
        int line;
        log_message_type type;
        int thread;
        std::string message{};
    };

    class log_message
    {
        public:
            explicit log_message(
                const char* file,            // __FILE__
                const char* function,        // __func__
                int line,                    // __LINE__
                log_message_type type,       // log type
                int thread_id = 0            // thread id 
            );

            log_message_data get_data();
            log_message& operator<<(std::string&& message);

        private:
            log_message_data data;
    };
}