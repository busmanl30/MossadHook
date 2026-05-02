#include "platform_detect_macro.h"
#if defined(TARGET_ARCH_ARM64)

#include "core/assembler/assembler-arm64.h"

using namespace zz::arm64;

void set_routing_bridge_next_hop(MossadRegisterContext *ctx, void *address) {
  *(void **)(&ctx->general.x[TMP_REG_0.code()]) = address;
}

void get_routing_bridge_next_hop(MossadRegisterContext *ctx, void *address) {
}

#endif
