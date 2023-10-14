#include <core/logs/logger.hpp>
#include <core/utility/time.hpp>

#include <iostream>

namespace cpf::logs
{
    logger::logger(const logger_config& config)
    : directory(config.base_dir)
    {   
        log_connection = listen_logs([&](const log_data& data)
        {
            this->write_log(data);
        });

        LOG_MESSAGE_INFO << "STARTING LOGGING SESSION";        
    }

    void logger::write_log(const log_data& data)
    {
        auto entry = create_log_entry(data);
        std::cout << entry.str() << std::endl;
    }

    std::ostringstream logger::create_log_entry(const log_data& data)
    {
        static constexpr auto time_format{"%F %T"};

        std::ostringstream entry{};
        entry << utility::current_time_as_stream(time_format).str() << " | " 
            << log_type_literal(data.type) << " | " 
            << data.file.filename().string() << " - " 
            << data.function << " - " 
            << data.line << " | " 
            << data.message.str();
        return entry;
    }

    logger::~logger()
    {
        LOG_MESSAGE_INFO << "ENDING LOGGING SESSION";

        if(thread.joinable())
            thread.join();
    }
}