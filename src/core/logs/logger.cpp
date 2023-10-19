#include <core/logs/logger.hpp>
#include <core/utility/time.hpp>

#include <iostream>
#include <functional>

namespace cpf::logs
{
    logger::logger(const logger_config& config_)
    : base_logger(config_)
    , file(config_)
    {
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
            file.write_log(entry);
            std::cout << entry.str() << std::endl;
        }
    }

    std::ostringstream logger::create_log_entry(const log_data& data)
    {
        std::ostringstream entry{};
        entry << utility::current_time_as_str(time_format) << " | " 
            << log_type_literal(data.type) << " | " 
            << data.file.filename().string() << " - " 
            << data.function << " - " 
            << data.line << " | " 
            << data.message.str();
        return entry;
    }
}