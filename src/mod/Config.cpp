#pragma once

#include <string>
#include <string_view>

#include <pl/Config.hpp>

namespace gradient_outline {

struct ModConfig {
    int version = 1;
    bool enabled = true;
    std::string message = "Gradient Outline is active";
};

nlohmann::json makeDefaultConfigJson();
nlohmann::json makeConfigSchemaJson();

} // namespace gradient_outline

template <> struct pl::config::Schema<gradient_outline::ModConfig> {
    static constexpr std::string_view title = "Gradient Outline Config";
    static constexpr std::string_view description = {};

    static constexpr FieldSchema field(std::string_view name) {
        if (name == "version")
            return {.title = "Version", .readOnly = true};
        if (name == "enabled")
            return {.title = "Enabled", .description = "Turns the gradient outline on or off."};
        if (name == "message")
            return {.title = "Message", .description = "Message shown when the mod is enabled."};
        return {};
    }
};
