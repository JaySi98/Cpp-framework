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

namespace cpf::logs 
{
    struct logger_config
    {
        std::filesystem::path base_dir;
    };
}