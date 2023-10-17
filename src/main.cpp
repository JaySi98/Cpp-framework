#include <atomic>
#include <chrono>
#include <string>
#include <thread>
#include <iostream>
#include <type_traits>

#include <core/logs/log_interface.hpp>
#include <core/logs/log_message.hpp>
#include <core/logs/logger.hpp>

//temp
#include <boost/version.hpp>
#include <core/utility/time.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

void print(const cpf::logs::log_data& data)
{
    std::cout << "print: " << std::this_thread::get_id() << " "<< data.message.str() << "\n"; 
}

int main(/*int argc, char** argv*/) 
{
    // current boost version
    std::cout << "Using Boost "     
        << BOOST_VERSION / 100000     << "."  // major version
        << BOOST_VERSION / 100 % 1000 << "."  // minor version
        << BOOST_VERSION % 100                // patch level
        << std::endl;

    // logs
    cpf::logs::logger_config config;
    config.base_dir = "./build/logs";
    config.to_file = false;
    cpf::logs::logger logger(config);
    logger.block_log_type(cpf::logs::log_type::hint);


    // test threaded loop
    std::atomic<bool> refresh_ui_continue = true;
    std::thread refresh_ui([&] 
    {
        while (refresh_ui_continue) 
        {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1s); // 0.05s

            LOG_MESSAGE_INFO << "Hello INFO!";
            LOG_MESSAGE_HINT << "Hello INFO!";
        }
    });

    std::thread user_input([&] 
    {
        while (refresh_ui_continue) 
        {
            std::string str{};
            std::cin >> str;
            if(str == "s")
                refresh_ui_continue = false;
        }
    });

    refresh_ui.join();
    user_input.join();

    return EXIT_SUCCESS;
}