#pragma once

#include <string>
#include <filesystem>
#include <sstream>
//temp
#include <iostream>

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

    class log_message_data 
    {
    public:
        explicit log_message_data(
            const char* file_,
            const char* function_,
            int line_,
            std::string text_,
            log_message_type type_
        );
    
    private:
        log_message_type type;
        std::string message{};
        std::filesystem::path path{};
        std::string function{};
        int line;
    };

    class log_message
    {
        public:
            explicit log_message(
                const char* file,         // __FILE__
                const char* function,     // __func__
                int line,                    // __LINE__
                std::string text,            // log text
                log_message_type type,       // log type
                unsigned long thread_id = 0  // thread id 
            );
            log_message_data get_data();
            // log_message& operator<<(std::string& text_);
            ~log_message(){ std::cout << "eeeee" << std::endl;};

        private:
            log_message_data data;
            // std::wostringstream message;
    };
}