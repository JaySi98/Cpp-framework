#include <core/thread/thread.hpp>

namespace cpf::thread
{
    thread::thread()
    {

    }

    thread::~thread()
    {
        stop();
        if(thread_.joinable())
        {
            thread_.join();
        }
    }

    void thread::set_component(component* comp)
    {
        component_ = comp;
    }

    void thread::start()
    {
        running = true;
        thread_ = std::thread(&thread::loop, this, std::ref(component_));
    }

    void thread::stop()
    {
        running = false;
    }

    void thread::loop(std::atomic<component*>& comp)
    {
        while(running)
        {
        }
    }
}