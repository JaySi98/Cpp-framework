#include <core/logs/log_file.hpp>
#include <core/utility/time.hpp>

#include <regex>
#include <vector>
#include <algorithm>

namespace
{
    constexpr auto log_ext{".log"};
    constexpr auto date_format{"%F"};

    int get_session_numer(const std::filesystem::path& dir)
    {
        int largest_number = 0;
        std::regex regex_number(R"(\d+)");

        for (const auto& entry : fs::directory_iterator(dir)) 
        {
            if (fs::is_regular_file(entry)) 
            {
                std::string file_name = entry.path().filename().string();

                // Search for numbers at the end of the file name
                std::smatch match;
                if (std::regex_search(file_name, match, regex_number))
                {
                    int number = std::stoi(match.str());

                    if (number > largest_number) 
                    {
                        largest_number = number;
                    }
                }
            }
        }

        return largest_number;
    }

    void remove_oldest_logs(const std::filesystem::path& dir, int days_to_keep)
    {
        std::vector<std::pair<fs::directory_entry, std::string>> directories;

        for (const auto& entry : fs::directory_iterator(dir)) {
            if (fs::is_directory(entry)) {
                directories.push_back(std::make_pair(entry, entry.path().filename().string()));
            }
        }

        if(directories.size() > static_cast<std::size_t>(days_to_keep))
        {
            std::sort(directories.begin(), directories.end(), [](const auto& a, const auto& b) 
            {
                return a.second < b.second;
            });

            std::size_t num_to_remove = directories.size() - static_cast<std::size_t>(days_to_keep);

            for (std::size_t i = 0; i < num_to_remove; ++i) {
                fs::remove_all(directories[i].first);
                LOG_MESSAGE_INFO << "Removed log directory: " << directories[i].first.path(); 
            }
        }
    }
}

namespace cpf::logs
{
    log_file::log_file(const logger_config& config_)
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
        if(fs::exists(config_.base_dir))
        {
            remove_oldest_logs(config_.base_dir, config_.days_to_keep);
        }
        else
        {
            fs::create_directory(config_.base_dir);
        }

        const auto today{utility::current_time_as_str(date_format)};
        const auto current_dir{config_.base_dir / today};

        // create log dir for todays logs
        if(!fs::exists(current_dir))
        {
            fs::create_directory(current_dir);
        }

        int last_session{get_session_numer(current_dir)};
        if(!config_.append || last_session == 0)
        {
            ++last_session;
        }

        const auto filename{config_.file_name.string() + '_' + std::to_string(last_session) + log_ext};
        file_path = current_dir / filename;
        file = std::ofstream{file_path, std::ios_base::app};

    }

    void log_file::write_log(const std::ostringstream& entry)
    {
        if(file.is_open())
        {
            file << entry.str() << '\n';
        }
    }
}