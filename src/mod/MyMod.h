#pragma once

#include <optional>

#include "mod/Config.h"

#include <pl/Mod.hpp>

namespace gradient_outline {

class GradientOutlineMod {
  public:
    static GradientOutlineMod &instance();

    GradientOutlineMod();

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

} // namespace gradient_outline
