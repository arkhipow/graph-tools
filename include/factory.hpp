#pragma once

#include <memory>
#include <type_traits>

struct ObjectUnit {
    virtual ~ObjectUnit() = default;
};

class UnitFactory final {
public:
    template <typename T, typename... Args>
    requires (std::is_base_of_v<ObjectUnit, T> && !std::is_same_v<T, ObjectUnit> && !std::is_abstract_v<T>)
    [[nodiscard]] static std::unique_ptr<T> Create(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
};