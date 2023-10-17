#pragma once

/*
-------------- CPF - Jakub Szkiłądź September 2023 --------------
component: core/logs
file: logger.hpp
description:
    class that writes logs to specified file and console     
-----------------------------------------------------------------
*/

#include <memory>
#include <thread>
#include <sstream>
#include <set>

#include <core/logs/log_interface.hpp>
#include <core/logs/log_message.hpp>
#include <core/logs/logger_config.hpp>
#include <core/logs/log_file.hpp>

namespace cpf::logs
{
    class logger
    {
    public:
        logger(const logger_config& config);
        ~logger();

        void block_log_type(const log_type& type);
        void clear_blocked();

    private:
        void write_log(const log_data& data);
        std::ostringstream create_log_entry(const log_data& data);

        logger_config config;
        log_file file;
        std::set<log_type> blocked_logs;
        std::thread thread;
        boost::signals2::connection log_connection;
    };
}
