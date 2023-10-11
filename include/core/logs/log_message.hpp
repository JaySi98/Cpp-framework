#pragma once

/*
-------------- CPF - Jakub Szkiłądź September 2023 --------------
component: core/logs
file: log_message.hpp
description:
    File contains helper class for easier log_data creation     
-----------------------------------------------------------------
*/

#include <string>

#include <core/logs/log_data.hpp>

namespace cpf::logs 
{
    class log_message
    {
    public:
        explicit log_message(
            const char* file,       // __FILE__
            const char* function,   // __func__
            int line,               // __LINE__
            log_type type,          // log type
            int thread_id = 0       // thread id 
        );
        ~log_message();

        const log_data& get_data();
        log_message& operator<<(std::string&& message);

    private:
        log_data data;
    };
}

#define LOG_MESSAGE_HINT    cpf::logs::log_message(__FILE__, __func__, __LINE__, cpf::logs::log_type::hint)
#define LOG_MESSAGE_INFO    cpf::logs::log_message(__FILE__, __func__, __LINE__, cpf::logs::log_type::information)
#define LOG_MESSAGE_WARNING cpf::logs::log_message(__FILE__, __func__, __LINE__, cpf::logs::log_type::warning)
#define LOG_MESSAGE_CAUTION cpf::logs::log_message(__FILE__, __func__, __LINE__, cpf::logs::log_type::caution)
#define LOG_MESSAGE_ERROR   cpf::logs::log_message(__FILE__, __func__, __LINE__, cpf::logs::log_type::error)
#define LOG_MESSAGE_FATAL   cpf::logs::log_message(__FILE__, __func__, __LINE__, cpf::logs::log_type::fatal)