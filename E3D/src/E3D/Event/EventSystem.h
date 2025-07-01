#pragma once

#include <functional>
#include <list>
#include <utility>

#include "E3D/Core/Window.h"

namespace E3D {
    enum class EventType {
        WindowResize,
        WindowClose,
        KeyboardInput,
        KeyboardChar,
        MouseButton,
        MouseScroll,
        MouseMoved,
    };

    enum class Action {
        Press = 1,   // GLFW_PRESS
        Release = 0, // GLFW_RELEASE
        Repeat = 2,  // GLFW_REPEAT
    };

    #define REGISTER_EVENT_CALLBACK(eventName, callbackType)                \
        using eventName##Callback = callbackType;                           \
        template <>                                                         \
        struct EventCallbackType<EventType::eventName> {                    \
        using type = eventName##Callback;                                   \
    };

    template <EventType>
    struct EventCallbackType;

    REGISTER_EVENT_CALLBACK(WindowResize, std::function<void(int, int)>)

    REGISTER_EVENT_CALLBACK(WindowClose, std::function<void()>)

    REGISTER_EVENT_CALLBACK(KeyboardInput, std::function<void(int, Action)>)

    REGISTER_EVENT_CALLBACK(KeyboardChar, std::function<void(unsigned int)>)

    REGISTER_EVENT_CALLBACK(MouseButton, std::function<void(int, Action)>)

    REGISTER_EVENT_CALLBACK(MouseScroll, std::function<void(double)>)

    REGISTER_EVENT_CALLBACK(MouseMoved, std::function<void(double, double)>)

    template <EventType ET>
    using ListenerHandle = typename std::list<typename EventCallbackType<ET>::type>::iterator;

    class EventSystem {
        friend class Application;
        friend class ScopedEventListener;

        static void Init(GLFWwindow* window);

        template <EventType ET>
        static ListenerHandle<ET> Register(typename EventCallbackType<ET>::type callback) {
            auto& listeners = GetListeners<ET>();
            return listeners.insert(listeners.end(), std::move(callback));
        }

        template <EventType ET>
        static void Unregister(ListenerHandle<ET> handle) {
            auto& listeners = GetListeners<ET>();
            listeners.erase(handle);
        }

        template <EventType ET>
        static void Dispatch(auto&&... args) {
            for (auto& cb : GetListeners<ET>()) {
                cb(std::forward<decltype(args)>(args)...);
            }
        }

        template <EventType ET>
        static std::list<typename EventCallbackType<ET>::type>& GetListeners() {
            static std::list<typename EventCallbackType<ET>::type> listeners;
            return listeners;
        }
    };

    #define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

    class ScopedEventListener {
    public:
        ScopedEventListener() = default;

        ~ScopedEventListener() {
            for (auto& cleanup : cleanups)
                cleanup();
        }

        ScopedEventListener(const ScopedEventListener&) = delete;
        ScopedEventListener& operator=(const ScopedEventListener&) = delete;

        template <EventType ET>
        void Subscribe(typename EventCallbackType<ET>::type callback) {
            auto handle = EventSystem::Register<ET>(std::move(callback));
            cleanups.emplace_back([handle] { EventSystem::Unregister<ET>(handle); });
        }

    private:
        std::vector<std::function<void()>> cleanups;
    };
}
