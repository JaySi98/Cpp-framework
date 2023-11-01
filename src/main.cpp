#include <atomic>
#include <chrono>
#include <string>
#include <thread>
#include <iostream>
#include <type_traits>
#include <filesystem>
#include <fstream>

#include <core/logs/log_interface.hpp>
#include <core/logs/log_message.hpp>
#include <core/logs/logger.hpp>

//temp
#include <core/thread/thread.hpp>
#include <core/utility/time.hpp>
#include <boost/version.hpp>

int main(/*int argc, char** argv*/) 
{
    // current boost version ------------------------------------- //
    std::cout << "BOOST VERSION: "     
        << BOOST_VERSION / 100000     << "."  // major version
        << BOOST_VERSION / 100 % 1000 << "."  // minor version
        << BOOST_VERSION % 100                // patch level
        << '\n';
    std::cout << "MAIN THREAD: "<< std::this_thread::get_id() << '\n';


    // // test thread  ---------------------------------------------- //
    namespace fs = std::filesystem;
    
    cpf::logs::logger_config config;
    config.base_dir = fs::absolute("build/logs");
    config.append = true;
    config.days_to_keep = 5;

    cpf::logs::logger logger(config);
    logger.block_log_type(cpf::logs::log_type::hint);


    // test threaded loop ---------------------------------------- //
    std::atomic<bool> program_active = true;
    std::thread user_input([&] 
    {
        std::cout << "MAIN LOOP: "<< std::this_thread::get_id() << '\n';

        // using namespace std::chrono_literals;
        // std::this_thread::sleep_for(1s); // 0.05s

        while (program_active) 
        {
            std::string str{};
            std::cin >> str;

            if(str == "stop")
            {
                program_active = false;
                // loop.stop();
            }
            else if(str == "clear")
            {
                logger.clear_blocked();
            }
            else if(str == "print")
            {
                LOG_MESSAGE_INFO << "print INFO";
                LOG_MESSAGE_HINT << "print HINT";
            }                
        }
    });

    user_input.join();
    // ----------------------------------------------------------- //

    return EXIT_SUCCESS;
}