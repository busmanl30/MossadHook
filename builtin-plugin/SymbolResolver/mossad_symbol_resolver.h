#pragma once

#if defined(BUILDING_INTERNAL)
#include "macho/mossad_symbol_resolver_priv.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

void *MossadSymbolResolver(const char *image_name, const char *symbol_name);

#ifdef __cplusplus
}
#endif