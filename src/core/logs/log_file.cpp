#include <core/logs/log_file.hpp>

namespace cpf::logs
{
    constexpr auto log_ext{".log"};
    constexpr auto date_format{"%F"};

    log_file::log_file(const logger_config& config_)
    : file_path(config.base_dir/config.file_name)
    {
        manage_files(config_);
    }

    log_file::~log_file()
    {
        if(file.is_open())
        {
            file.flush();
            file.close();
        }
    }

    void log_file::manage_files(const logger_config& config_)
    {
        // create log file dir if it doesn't exist
        if(!fs::exists(config_.base_dir))
        {
            fs::create_directory(base_dir);
        }
                
        if(config_.append)
        {
            // find newest file and open it
            
            // TODO
        }
        else
        {
            // create new file            
            
            const auto date = current_time_as_str(date_format);
            // TODO
            file = std::ofstream{file_path};
        }
    }

    void log_file::write_log(const std::ostringstream& entry)
    {
        if(file.is_open())
        {
            file << entry.str() << '\n';
        }
    }
}