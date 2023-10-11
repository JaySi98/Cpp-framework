#include <core/logs/log_message.hpp>

#include <boost/signals2.hpp>
#include <boost/signals2/connection.hpp>

#include <core/logs/log_interface.hpp>

namespace {
    boost::signals2::signal<void(const cpf::logs::log_data&)> signal_log;
}

namespace cpf::logs 
{
    // from log_interface.hpp
    boost::signals2::connection listen_logs(std::function<void(const log_data&)> slot)
    {
        return signal_log.connect(std::move(slot));
    }

    log_message::log_message(
        const char* file,
        const char* function,
        int line,
        log_type type,
        int thread_id
    ) : data(file, function, line, type, thread_id)
    {}

    log_message::~log_message()
    {
        // send new log entry to listeners
        signal_log(data);
    }

    const log_data& log_message::get_data() 
    {
        return data;
    }
        
    log_message& log_message::operator<<(std::string&& message)
    {
        // TODO
        data.message = std::forward<std::string>(message);
        return *this;
    }
};
