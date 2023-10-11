#include <atomic>
#include <chrono>
#include <string>
#include <thread>
#include <iostream>
#include <type_traits>

#include <core/logs/log_interface.hpp>
#include <core/logs/log_message.hpp>
#include <core/logs/logger.hpp>

#include <boost/version.hpp>

int main(int argc, char** argv) 
{

    std::cout << "Using Boost "     
          << BOOST_VERSION / 100000     << "."  // major version
          << BOOST_VERSION / 100 % 1000 << "."  // minor version
          << BOOST_VERSION % 100                // patch level
          << std::endl;

    cpf::logs::logger_config config{"."};
    cpf::logs::logger logger(config);

    cpf::logs::listen_logs([&](const cpf::logs::log_data& data)
    {
        std::cout << "main listener: ";
        std::cout << data.line << " | " << data.message << std::endl;
    });

    LOG_MESSAGE_HINT << "dupa";


    // std::atomic<bool> refresh_ui_continue = true;
    // std::thread refresh_ui([&] 
    // {
    //     while (refresh_ui_continue) 
    //     {
    //         using namespace std::chrono_literals;
    //         std::this_thread::sleep_for(1s); // 0.05s

    //         std::cout << "Hello World!" << std::endl;
    //     }
    // });

    // std::thread user_input([&] 
    // {
    //     while (refresh_ui_continue) 
    //     {
    //         std::string str{};
    //         std::cin >> str;
    //         if(str == "stop")
    //             refresh_ui_continue = false;
    //     }
    // });

    // refresh_ui.join();
    // user_input.join();

    return EXIT_SUCCESS;
}