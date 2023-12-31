#pragma once

/*
-------------- CPF - Jakub Szkiłądź September 2023 --------------
component: core/logs
file: log_file.hpp
description:
    class that manages log folder and files     
-----------------------------------------------------------------
*/

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <core/logs/log_interface.hpp>
#include <core/logs/log_message.hpp>
#include <core/logs/logger_config.hpp>

namespace fs = std::filesystem;

namespace cpf::logs
{
    class log_file 
    {
    public:
        log_file(const logger_config& config);
        ~log_file();

        void write_log(const std::ostringstream& entry);
        void close_file();
        void open_file(const std::filesystem::path& file_name);

    private:
        void manage_files(bool append);

        std::filesystem::path file_path;
        std::ofstream file;
    };
}