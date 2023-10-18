#include <core/logs/logger.hpp>
#include <core/utility/time.hpp>

#include <iostream>
#include <functional>

namespace cpf::logs
{
    logger::logger(const logger_config& config_)
    : config(config_)
    , file(config)
    , blocked_logs()
    {
        using namespace std::placeholders;  // for _1
        log_connection = listen_logs(std::bind(&logger::write_log, this, _1));

        LOG_MESSAGE_INFO << "STARTING LOGGING SESSION";
    }

    logger::~logger()
    {
        LOG_MESSAGE_INFO << "ENDING LOGGING SESSION";
    }

    void logger::write_log(const log_data& data)
    {
        if(auto search = blocked_logs.find(data.type); search == blocked_logs.end())
        {
            auto entry = create_log_entry(data);

            if(config.to_file)
            {
                file.write_log(entry);
            }

            if(config.to_console)
            {
                std::cout << entry.str() << std::endl;
            }
        }
    }

    std::ostringstream logger::create_log_entry(const log_data& data)
    {
        std::ostringstream entry{};
        entry << utility::current_time_as_str(config.time_format) << " | " 
            << log_type_literal(data.type) << " | " 
            << data.file.filename().string() << " - " 
            << data.function << " - " 
            << data.line << " | " 
            << data.message.str();
        return entry;
    }

    void logger::block_log_type(const log_type& type)
    {
        blocked_logs.insert(type);
    }

    void logger::clear_blocked()
    {
        blocked_logs.clear();
    }
}