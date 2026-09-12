#include "mod/MyMod.h"

#include <filesystem>

#include <pl/Mod.hpp>

namespace gradient_outline {

GradientOutlineMod &GradientOutlineMod::instance() {
    static GradientOutlineMod instance;
    return instance;
}

GradientOutlineMod::GradientOutlineMod() : mSelf(*ll::mod::NativeMod::current()) {}

bool GradientOutlineMod::load() {
    auto &self = getSelf();
    self.getLogger().debug("Loading Gradient Outline mod...");

    std::error_code ec;

    // Create data folder
    std::filesystem::create_directories(self.getDataDir(), ec);
    if (ec) {
        self.getLogger().error("Failed to create data directory: {}", ec.message());
        return false;
    }

    // Create config folder
    std::filesystem::create_directories(self.getConfigDir(), ec);
    if (ec) {
        self.getLogger().error("Failed to create config directory: {}", ec.message());
        return false;
    }

    // Load config
    mConfigFile.emplace();
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
