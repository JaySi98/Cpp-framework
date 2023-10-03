#include <core/logs/logger.hpp>

//temp
#include <iostream>

namespace cpf::logs 
{
    logger::logger()
    { }

    void logger::write_log_message(log_message message)
    {
        // std::cout << message.get_data().message << std::endl;
        std::cout << "print message" << std::endl;

    }
}