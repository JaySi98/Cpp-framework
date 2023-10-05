#pragma once

#include <core/logs/log_message.hpp>

namespace cpf::logs 
{
    class logger
    {
    public:
        logger(); //std::filesystem::path

    private:
    };
}

#define LOG_MESSAGE_HINT    cpf::logs::log_message(__FILE__, __func__, __LINE__, cpf::logs::log_message_type::hint)
#define LOG_MESSAGE_INFO    cpf::logs::log_message(__FILE__, __func__, __LINE__, cpf::logs::log_message_type::information)
#define LOG_MESSAGE_WARNING cpf::logs::log_message(__FILE__, __func__, __LINE__, cpf::logs::log_message_type::warning)
#define LOG_MESSAGE_CAUTION cpf::logs::log_message(__FILE__, __func__, __LINE__, cpf::logs::log_message_type::caution)
#define LOG_MESSAGE_ERROR   cpf::logs::log_message(__FILE__, __func__, __LINE__, cpf::logs::log_message_type::error)
#define LOG_MESSAGE_FATAL   cpf::logs::log_message(__FILE__, __func__, __LINE__, cpf::logs::log_message_type::fatal)