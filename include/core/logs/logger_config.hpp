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
        std::filesystem::path file_name{"session_"};
        std::string time_format{"%F %T"};

        bool new_file = false;  // logger will not create new file 
                                // but will continue to write newest in the folder
        bool to_file = true;    // logger will write to base_dir/file_name
        bool to_console = true; // logger will write to standard output
    };
}