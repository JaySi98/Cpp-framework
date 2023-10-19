#include <core/logs/log_file.hpp>

namespace cpf::logs
{
    log_file::log_file(const logger_config& config_)
    : config(config_)
    {
        create_file();
    }

    log_file::~log_file()
    {
        if(file.is_open())
        {
            file.flush();
            file.close();
        }
    }

    void log_file::create_file()
    {
        if(fs::exists(config.base_dir))
        {
            file = std::ofstream{config.base_dir/config.file_name};
        }
        else
        {
            fs::create_directory(config.base_dir);
        }
    }

    void log_file::write_log(const std::ostringstream& entry)
    {
        file << entry.str() << '\n';
    }
}