#pragma once

/*
-------------- CPF - Jakub Szkiłądź September 2023 --------------
component: core/logs
file: logger_config.hpp
description:
    Struct used to initialize logger class
-----------------------------------------------------------------
*/

#include <filesystem>
#include <string>

namespace cpf::logs 
{
    struct logger_config
    {
        std::filesystem::path base_dir{"/var/log/cpf"};
        std::filesystem::path file_name{"session"};
        std::string time_format{"%F %T"};

        bool append = true;     // logger will not create new file
                                // but will continue to write to the newest in the folder
        int files_to_keep = 10; // number of log files to be kept
    };
}