#pragma once

#include <array>
#include <algorithm>
#include <stdexcept>

namespace cpf::utility
{
    template<typename Key, typename Value, std::size_t Size>
    struct type_literal_map
    {
        std::array<std::pair<Key, Value>, Size> data;

        [[nodiscard]] constexpr Value at(const Key& key) const
        {
            const auto iter = std::find_if(data.begin(), data.end(),[&key](const auto& v)
            {
                return v.first == key;
            });

            if(iter != data.end())
            {
                return iter->second;
            }
            else
            {
                throw std::range_error("Not Found");
            }
        }
    };
}