#pragma once

/*
-------------- CPF - Jakub Szkiłądź September 2023 --------------
component: core/thread
file: thread.hpp
description:

-----------------------------------------------------------------
*/

#include <thread>
#include <atomic>
#include <memory>
#include <string>
#include <iostream>

namespace cpf::thread
{
    class component;

    class thread
    {
        friend class component;

    public:
        thread();
        ~thread();
        
        void start();
        void stop();

    private:
        void set_component(component* comp);
        void loop(std::atomic<component*>& comp);

        std::thread thread_;
        std::atomic<component*> component_;
        std::atomic<bool> running;
    };
}