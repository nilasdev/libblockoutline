#include "mod/MyMod.h"

#include <filesystem>

#include <pl/Mod.hpp>
#include <pl/ModMenu.hpp>

namespace high_gyro {

HighGyroMod &HighGyroMod::instance() {
    static HighGyroMod instance;
    return instance;
}

HighGyroMod::HighGyroMod() : mSelf(*ll::mod::NativeMod::current()) {}

bool HighGyroMod::load() {
    auto &self = getSelf();
    self.getLogger().info("Loading High Gyro...");

    std::error_code ec;
    std::filesystem::create_directories(self.getDataDir(), ec);
    std::filesystem::create_directories(self.getConfigDir(), ec);

    mConfigFile.emplace();
    if (!mConfigFile->load()) {
        self.getLogger().warn("Failed to load config, using defaults");
    }
    mConfig = mConfigFile->value();

    self.getLogger().info("High Gyro loaded. Sensitivity = {}", mConfig.sensitivity);
    return true;
}

bool HighGyroMod::enable() {
    auto &self = getSelf();
    self.getLogger().info("Enabling High Gyro...");

    if (!mConfig.enabled) {
        self.getLogger().info("High Gyro is disabled in config");
        return true;
    }

    // Register Mod Menu so you can change sensitivity in-game
    pl::modmenu::ModuleBuilder("high_gyro.main", "High Gyro")
        .modId(self.getId())
        .description("Custom high sensitivity gyroscope (Deadzone 0, Smoothing 0)")
        .defaultEnabled(mConfig.enabled)
        .config("sensitivity", "Sensitivity", pl::modmenu::ConfigType::SliderFloat,
                std::to_string(mConfig.sensitivity), "0.5", "10.0")
        .registerModule();

    // ============================================
    // TODO: Real gyroscope reading + camera control will go here
    // For now this is the clean structure ready for the gyro code
    // ============================================

    self.getLogger().info("High Gyro enabled with sensitivity {}", mConfig.sensitivity);
    return true;
}

bool HighGyroMod::disable() {
    getSelf().getLogger().info("Disabling High Gyro...");
    return true;
}

bool HighGyroMod::unload() {
    getSelf().getLogger().info("Unloading High Gyro...");
    mConfigFile.reset();
    return true;
}

} // namespace high_gyro    mConfigFile.emplace();
    if (!mConfigFile->load()) {
        self.getLogger().warn("Failed to load config, using defaults");
    }
    mConfig = mConfigFile->value();

    self.getLogger().info("Gradient Outline mod loaded successfully");
    return true;
}

bool GradientOutlineMod::enable() {
    auto &self = getSelf();
    self.getLogger().debug("Enabling Gradient Outline mod...");

    if (!mConfig.enabled) {
        self.getLogger().info("Mod is disabled in config");
        return true;
    }

    // ============================================
    // TODO: Stage 2 - Hook the selection box drawing function here
    // This is where we will intercept the normal outline
    // and replace it with our custom gradient outline.
    // ============================================

    self.getLogger().info("Gradient Outline is now active");
    return true;
}

bool GradientOutlineMod::disable() {
    auto &self = getSelf();
    self.getLogger().debug("Disabling Gradient Outline mod...");

    // ============================================
    // TODO: Remove the hook / clean up rendering here
    // ============================================

    return true;
}

bool GradientOutlineMod::unload() {
    getSelf().getLogger().debug("Unloading Gradient Outline mod...");
    mConfigFile.reset();
    return true;
}

} // namespace gradient_outline        self.getLogger().warn("Failed to load typed config");
        return false;
    }
    mConfig = mConfigFile->value();

    self.getLogger().info("Loaded {} from {}", self.getName(), self.getModDir().string());
    return true;
}

bool ClangeMeMod::enable() {
    auto &self = getSelf();
    self.getLogger().debug("Enabling...");
    if (!mConfig.enabled) {
        self.getLogger().info("clange_me is disabled by config");
        return true;
    }

    self.getLogger().info("Config message: {}", mConfig.message);
    return true;
}

bool ClangeMeMod::disable() {
    getSelf().getLogger().debug("Disabling...");
    // Undo enable-time state here.
    return true;
}

bool ClangeMeMod::unload() {
    getSelf().getLogger().debug("Unloading...");
    // Release load-time resources here.
    mConfigFile.reset();
    return true;
}

} // namespace clange_me
