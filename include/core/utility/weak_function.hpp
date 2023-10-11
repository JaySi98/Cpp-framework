#pragma once

/*
-------------- CPF - Jakub Szkiłądź September 2023 --------------
component: core/utility
file: weak_function.hpp
description:
         
-----------------------------------------------------------------
*/

#include <functional>
#include <memory>

namespace cpf::utility
{
    template<typename T, typename Function>
    class weak_function
    {
    public:
        template<typename Ptr>
        weak_function(Ptr&& ptr_, Function&& func_) : ptr(std::forward<Ptr>(ptr_)), function(std::forward<Ptr>(func_)) 
        { }

        template<typename Ptr>
        weak_function(Ptr&& ptr_, const Function& func_) : ptr(std::forward<Ptr>(ptr_)), function(func_)
        { }

        weak_function(weak_function&& rhs) : ptr(std::move(rhs.ptr)), function(std::move(rhs.function))
        { }

        weak_function(const weak_function& rhs) = default;

        template<typename... Args>
        void operator()(Args&&... t) const
        {
            auto shared = ptr.lock();
            if(shared)
            {
                handler(*shared, std::forward<Args>(t)...);
            }
        }

    private:
        std::weak_ptr<T> ptr;
        Function function;
    };

    template<typename T, typename Function>
    class weak_member
    {
    public:
        template<typename Ptr>
        weak_member(Ptr&& ptr_, const Function& func_) : ptr(std::forward<Ptr>(ptr_)), function(func_)
        { }

        weak_member(weak_member&& rhs) : ptr(std::move(rhs.ptr)), function(std::move(rhs.function))
        { }

        weak_member(const weak_member& rhs) = default;

        template<typename... Args>
        void operator()(Args&&... t) const
        {
            auto shared = ptr.lock();
            if(shared)
            {
                (*shared.*function)(std::forward<Args>(t)...);
            }
        }

    private:
        std::weak_ptr<T> ptr;
        Function function;
    };

    template<typename Ptr, typename Fn>
    typename std::enable_if<!std::is_member_function_pointer<typename std::remove_reference<Fn>::type>::value,
    weak_function<typename std::remove_reference<Ptr>::type::element_type, Fn>>::type
    make_weak_function(Ptr&& ptr, Fn&& fn)
    {
        return weak_function<typename std::remove_reference<Ptr>::type::element_type, Fn>(std::forward<Ptr>(ptr),std::forward<Fn>(fn));
    }

    template<typename Ptr, typename Fn>
    typename std::enable_if<std::is_member_function_pointer<typename std::remove_reference<Fn>::type>::value,
    weak_member<typename std::remove_reference<Ptr>::type::element_type, Fn>>::type
    make_weak_member(Ptr&& ptr, Fn&& fn)
    {
        return weak_member<typename std::remove_reference<Ptr>::type::element_type, Fn>(std::forward<Ptr>(ptr),std::forward<Fn>(fn));
    }
}