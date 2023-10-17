#pragma once

/*
-------------- CPF - Jakub Szkiłądź September 2023 --------------
component: core/logs
file: log_interface.hpp
description:
    Entry point to use log component.

-----------------------------------------------------------------
*/

#include <functional>
#include <boost/signals2.hpp>
#include <boost/signals2/connection.hpp>

#include <core/logs/log_data.hpp>

namespace cpf::logs 
{
    boost::signals2::connection listen_logs(std::function<void(const log_data&)> slot);
}
