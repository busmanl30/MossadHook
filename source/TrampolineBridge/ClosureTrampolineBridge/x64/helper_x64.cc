#include "platform_detect_macro.h"
#if defined(TARGET_ARCH_X64)

#include "mossad/mossad_internal.h"

void set_routing_bridge_next_hop(MossadRegisterContext *ctx, void *address) {
  ctx->ret = (uint64_t)address;
}

void get_routing_bridge_next_hop(MossadRegisterContext *ctx, void *address) {
}

#endif