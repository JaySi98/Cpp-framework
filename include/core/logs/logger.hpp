#pragma once

#include <core/logs/log_message.hpp>

namespace cpf::logs 
{
    class logger
    {
        public:
        logger(); //std::filesystem::path
        static void write_log_message(log_message message);

        private:
    };
}

#define LOG_MESSAGE_HINT(text)     cpf::logs::log_message(__FILE__, __func__, __LINE__, text, cpf::logs::log_message_type::hint);
// #define LOG_MESSAGE_HINT(text)     cpf::logs::logger.write_log_message(cpf::logs::log_message(__FILE__, __func__, __LINE__, text, cpf::logs::log_message_type::hint));

#define LOG_MESSAGE_INFO(text)     cpf::logs::logger.write_log_message(cpf::logs::log_message(__FILE__, __func__, __LINE__, text, cpf::logs::log_message_type::information));
#define LOG_MESSAGE_WARNING(text)  cpf::logs::logger.write_log_message(cpf::logs::log_message(__FILE__, __func__, __LINE__, text, cpf::logs::log_message_type::warning));
#define LOG_MESSAGE_CAUTION(text)  cpf::logs::logger.write_log_message(cpf::logs::log_message(__FILE__, __func__, __LINE__, text, cpf::logs::log_message_type::caution));
#define LOG_MESSAGE_ERROR(text)    cpf::logs::logger.write_log_message(cpf::logs::log_message(__FILE__, __func__, __LINE__, text, cpf::logs::log_message_type::error));
#define LOG_MESSAGE_FATAL(text)    cpf::logs::logger.write_log_message(cpf::logs::log_message(__FILE__, __func__, __LINE__, text, cpf::logs::log_message_type::fatal));