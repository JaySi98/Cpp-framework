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

#include <core/logs/log_interface.hpp>
#include <core/logs/log_message.hpp>
#include <core/logs/logger_config.hpp>

namespace cpf::logs
{
    class logger
    {
    public:
        logger(const logger_config& config);
        ~logger();

    private:
        void write_log(const log_data& data);

        std::thread thread;
        std::filesystem::path directory;
        boost::signals2::connection log_connection;
    };
}
