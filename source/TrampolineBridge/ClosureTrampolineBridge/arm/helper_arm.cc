#include "platform_detect_macro.h"
#if defined(TARGET_ARCH_ARM)

#include "mossad/mossad_internal.h"

void set_routing_bridge_next_hop(MossadRegisterContext *ctx, void *address) {
  *reinterpret_cast<void **>(&ctx->general.regs.r12) = address;
}

void get_routing_bridge_next_hop(MossadRegisterContext *ctx, void *address) {
}

#endif