#pragma once

/*
-------------- CPF - Jakub Szkiłądź September 2023 --------------
component: core/logs
file: logger.hpp
description:
    class that writes logs to specified file and console
-----------------------------------------------------------------
*/


#include <core/logs/base_logger.hpp>
#include <core/logs/log_file.hpp>

namespace cpf::logs
{
    class logger : public base_logger
    {
    public:
        logger(const logger_config& config);
        ~logger();

        void write_log(const log_data& data) override;
        std::ostringstream create_log_entry(const log_data& data) override;

    private:
        log_file file;
    };
}
