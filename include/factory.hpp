#pragma once

#include "utils.hpp"

#include <type_traits>

namespace FactoryUnit {
    template <typename T, typename... Args>
    requires (std::is_base_of_v<IObjectUnit, T> && !std::is_same_v<T, IObjectUnit> && !std::is_abstract_v<T>)
    [[nodiscard]] std::unique_ptr<T> Create(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    inline std::unique_ptr<MeasurePixelUnit> Pixels(float x, float y) {
        return std::make_unique<MeasurePixelUnit>(x, y);
    }

    inline std::unique_ptr<MeasurePercentUnit> Percent(float x, float y) {
        return std::make_unique<MeasurePercentUnit>(x, y);
    }
}