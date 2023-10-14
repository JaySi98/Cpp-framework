#pragma once

/*
-------------- CPF - Jakub Szkiłądź September 2023 --------------
component: core/utility
file: time.hpp
description:
    header file to help with <chrono> library     
-----------------------------------------------------------------
*/

#include <chrono>
#include <sstream>

namespace cpf::utility
{
    std::ostringstream current_time_as_stream(const char* format);
};