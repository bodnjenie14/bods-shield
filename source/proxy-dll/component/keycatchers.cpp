#include <std_include.hpp>
#include "keycatchers.hpp"
#include "loader/component_loader.hpp"

#include <utilities/hook.hpp>
#include <utilities/concurrency.hpp>
#include <algorithm>

namespace keycatchers
{
    namespace
    {
        const std::vector<int> excluded_keys = { 
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 27
        };

        utilities::concurrency::container<std::vector<ke_typedef>, std::recursive_mutex> key_event_callbacks;
        utilities::concurrency::container<std::vector<ch_typedef>, std::recursive_mutex> char_event_callbacks;

        utilities::hook::detour cl_key_event_hook;
        void cl_key_event_stub(const int localClientNum, const int key, bool down, const unsigned int time)
        {
            if (down && std::find(excluded_keys.begin(), excluded_keys.end(), key) == excluded_keys.end())
            {
                key_event_callbacks.access([&](std::vector<ke_typedef>& callbacks)
                {
                    for (auto& func : callbacks) {
                        if (!func(localClientNum, key, down, time))
                            return;
                    }
                });
            }

            cl_key_event_hook.invoke<void>(localClientNum, key, down, time);
        }

        utilities::hook::detour cl_char_event_hook;
        void cl_char_event_stub(const int localClientNum, const int key, bool isRepeated)
        {
            if (std::find(excluded_keys.begin(), excluded_keys.end(), key) == excluded_keys.end())
            {
                char_event_callbacks.access([&](std::vector<ch_typedef>& callbacks)
                {
                    for (auto& func : callbacks) {
                        if (!func(localClientNum, key, isRepeated))
                            return;
                    }
                });
            }

            cl_char_event_hook.invoke<void>(localClientNum, key, isRepeated);
        }
    }

    void add_key_event(ke_typedef&& func)
    {
        key_event_callbacks.access([&func](std::vector<ke_typedef>& callbacks)
        {
            callbacks.push_back(std::move(func));
        });
    }

    void add_char_event(ch_typedef&& func)
    {
        char_event_callbacks.access([&func](std::vector<ch_typedef>& callbacks)
        {
            callbacks.push_back(std::move(func));
        });
    }

    class component final : public component_interface
    {
    public:
        void post_unpack() override
        {
            cl_key_event_hook.create(0x142839250_g, cl_key_event_stub);
            cl_char_event_hook.create(0x142836F80_g, cl_char_event_stub);
        }
    };
}

REGISTER_COMPONENT(keycatchers::component)
