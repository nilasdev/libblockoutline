#pragma once

#include <optional>

#include "mod/Config.h"

#include <pl/Mod.hpp>

namespace high_gyro {

class HighGyroMod {
  public:
    static HighGyroMod &instance();

    HighGyroMod();

    [[nodiscard]] ll::mod::NativeMod &getSelf() const { return mSelf; }

    bool load();
    bool enable();
    bool disable();
    bool unload();

  private:
    ll::mod::NativeMod &mSelf;
    ModConfig mConfig;
    std::optional<pl::config::ConfigFile<ModConfig>> mConfigFile;
};

} // namespace high_gyro
