#include <atomic>
#include <chrono>
#include <string>
#include <thread>
#include <iostream>
#include <type_traits>

#include <core/logs/logger.hpp>

int main(int argc, char** argv) 
{
    cpf::logs::logger m_logger;
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