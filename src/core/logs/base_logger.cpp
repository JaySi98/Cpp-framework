#include <core/logs/base_logger.hpp>

namespace cpf::logs
{
    base_logger::base_logger(const logger_config& config)
    : time_format(config.time_format)
    {
        using namespace std::placeholders;  // for _1
        log_connection = listen_logs(std::bind(&base_logger::write_log, this, _1));
    }

    base_logger::~base_logger()
    {
        log_connection.disconnect();
    }

    void base_logger::block_log_type(const log_type& type)
    {
        blocked_logs.insert(type);
    }
    
    void base_logger::clear_blocked()
    {
        blocked_logs.clear();
    }

    void base_logger::set_time_format(const std::string& format)
    {
        time_format = format;
    }
}