#pragma once

#include <string>
#include <string_view>

#include <pl/Config.hpp>

namespace high_gyro {

struct ModConfig {
    int version = 1;
    bool enabled = true;
    float sensitivity = 3.0f;   // Default multiplier
};

nlohmann::json makeDefaultConfigJson();
nlohmann::json makeConfigSchemaJson();

} // namespace high_gyro

template <> struct pl::config::Schema<high_gyro::ModConfig> {
    static constexpr std::string_view title = "High Gyro Config";
    static constexpr std::string_view description = {};

    static constexpr FieldSchema field(std::string_view name) {
        if (name == "version")
            return {.title = "Version", .readOnly = true};
        if (name == "enabled")
            return {.title = "Enabled", .description = "Turns High Gyro on or off."};
        if (name == "sensitivity")
            return {.title = "Sensitivity Multiplier", .description = "How strong the gyro is. 1.0 = normal, higher = faster."};
        return {};
    }
};
