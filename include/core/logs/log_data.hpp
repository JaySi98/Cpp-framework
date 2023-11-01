#pragma once

/*
-------------- CPF - Jakub Szkiłądź September 2023 --------------
component: core/logs
file: log_data.hpp
description:
    Contains basic data structure used by other parts of
log component.
    * log_type - enum specifing log severity 
    * log_data - contains basic information of a
    single log entry 
-----------------------------------------------------------------
*/

#include <filesystem>
#include <sstream>

namespace cpf::logs 
{
    enum class log_type
    {
        hint,
        information,
        warning,
        caution,
        error,
        fatal
    };

    const std::string_view log_type_literal(log_type type);

    struct log_data 
    {
        explicit log_data(
            const std::filesystem::path& file_,
            const std::string& function_,
            int line_,
            log_type type_,
            int thread_id
        );
    
        friend std::ostream& operator<<(std::ostream& os, const log_data& data);

        std::filesystem::path file{};
        std::string function{};
        int line;
        log_type type;
        int thread;
        std::ostringstream message{};
    };
};