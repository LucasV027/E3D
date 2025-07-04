#pragma once

#include <cassert>
#include <memory>

namespace E3D {
    #define panic(error) assert(false && error);

    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;

    template <typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    class SharedOnly : std::enable_shared_from_this<T> {
    protected:
        struct InternalTag {
            explicit InternalTag() = default;
        };
    };
}
