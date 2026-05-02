#pragma once

#include "mossad/mossad_internal.h"

#include "InterceptRouting/RoutingPlugin.h"

class NearBranchTrampolinePlugin : public RoutingPluginInterface {};

inline bool g_enable_near_trampoline = false;

PUBLIC extern "C" inline void mossad_set_near_trampoline(bool enable) {
  g_enable_near_trampoline = enable;
}