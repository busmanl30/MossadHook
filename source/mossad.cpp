#include "mossad.h"
#include "mossad/common.h"
#include "Interceptor.h"
#include "InterceptRouting/InlineHookRouting.h"
#include "InterceptRouting/InstrumentRouting.h"
#include "InterceptRouting/NearBranchTrampoline/NearBranchTrampoline.h"
#include "TrampolineBridge/ClosureTrampolineBridge/common_bridge_handler.h"
#include "MemoryAllocator/NearMemoryAllocator.h"
#include <stdint.h>

__attribute__((constructor)) static void ctor() {
  DEBUG_LOG("================================");
  DEBUG_LOG("Mossad");
  DEBUG_LOG("mossad in debug log mode, disable with cmake flag \"-DMOSSAD_DEBUG=OFF\"");
  DEBUG_LOG("================================");
}

PUBLIC int MossadDestroy(void *address) {
  __FUNC_CALL_TRACE__();
  if (!address) {
    ERROR_LOG("address is 0x0");
    return -1;
  }

  features::arm_thumb_fix_addr(address);
  features::apple::arm64e_pac_strip(address);

  auto entry = gInterceptor.find((addr_t)address);
  if (entry) {
    gInterceptor.remove((addr_t)address);
    entry->restore_orig_code();
    // FIXME: delete entry safely
    // delete entry;
    return 0;
  }

  return -1;
}

PUBLIC void mossad_set_options(bool enable_near_trampoline, mossad_alloc_near_code_callback_t alloc_near_code_callback) {
  mossad_set_near_trampoline(enable_near_trampoline);
  mossad_register_alloc_near_code_callback(alloc_near_code_callback);
}

PUBLIC uintptr_t placeholder() {
  uintptr_t x = 0;
  x += (uintptr_t)&MossadHook;
  x += (uintptr_t)&MossadInstrument;
  x += (uintptr_t)&mossad_set_near_trampoline;
  x += (uintptr_t)&common_closure_bridge_handler;
  x += (uintptr_t)&mossad_register_alloc_near_code_callback;
  return x;
}
