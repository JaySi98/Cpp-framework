#pragma once

/*
-------------- CPF - Jakub Szkiłądź September 2023 --------------
component: core/logs
file: base_logger.hpp
description:
    interface for all logger classes     
-----------------------------------------------------------------
*/

#include <memory>
#include <sstream>
#include <set>

#include <core/logs/log_interface.hpp>
#include <core/logs/log_message.hpp>
#include <core/logs/logger_config.hpp>

namespace cpf::logs
{
    class base_logger
    {
    public:
        base_logger(const logger_config& config);
        virtual ~base_logger();

        void block_log_type(const log_type& type);
        void clear_blocked();
        void set_time_format(const std::string& format);

    protected:
        virtual void write_log(const log_data& data) = 0;
        virtual std::ostringstream create_log_entry(const log_data& data) = 0;

        std::string time_format;
        std::set<log_type> blocked_logs;
        boost::signals2::connection log_connection;
    };
}