#include <core/logs/logger.hpp>

//temp
#include <iostream>
#include <core/utility/weak_function.hpp>

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
        std::cout << "logger:";
        std::cout << data.message << std::endl;
    }

    logger::~logger()
    {
        LOG_MESSAGE_INFO << "ENDING LOGGING SESSION";

        if(thread.joinable())
            thread.join();
    }
}