# MossadHook — Usage Examples

> *"אל תסתכל בקנקן אלא במה שיש בו"*
> "Do not look at the container, but at what is inside it." — Pirkei Avot 4:20

---

## Basic Function Hook

The simplest use of MossadHook — intercept a function, run your own logic, and optionally call the original.

```c
#include "mossad.h"
#include <stdio.h>

// Original function pointer
static int (*orig_open)(const char *path, int flags);

// Our replacement
int fake_open(const char *path, int flags) {
    printf("[MossadHook] open(\"%s\", %d)\n", path, flags);
    return orig_open(path, flags);
}

void install() {
    void *addr = MossadSymbolResolver(NULL, "open");
    MossadHook(addr, (void *)fake_open, (void **)&orig_open);
}
```

> *"הכל צפוי והרשות נתונה"*
> "Everything is foreseen, yet freedom of choice is granted." — Pirkei Avot 3:15

---

## Using the `install_hook_name` Macro

For convenience, MossadHook provides a macro that handles the boilerplate:

```c
#include "mossad.h"

install_hook_name(connect, int, int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    printf("[MossadHook] connect() intercepted on fd=%d\n", sockfd);
    return orig_connect(sockfd, addr, addrlen);
}

// Then somewhere in your initialization:
void setup() {
    void *sym = MossadSymbolResolver(NULL, "connect");
    install_hook_connect(sym);
}
```

> *"בִּמְקוֹם שֶׁאֵין אֲנָשִׁים, הִשְׁתַּדֵּל לִהְיוֹת אִישׁ"*
> "In a place where there are no men, strive to be a man." — Pirkei Avot 2:5

---

## Dynamic Binary Instrumentation

Use `MossadInstrument` to observe function calls without replacing them — pure surveillance:

```c
#include "mossad.h"
#include <stdio.h>

void on_recv(void *address, MossadRegisterContext *ctx) {
    // On ARM64, x0 = first argument (socket fd), x2 = third argument (length)
    printf("[MossadHook] recv() called — fd=%llu, len=%llu\n",
           ctx->general.regs.x0, ctx->general.regs.x2);
}

void install() {
    void *addr = MossadSymbolResolver(NULL, "recv");
    MossadInstrument(addr, on_recv);
}
```

> *"אֵיזֶהוּ חָכָם? הַלּוֹמֵד מִכָּל אָדָם"*
> "Who is wise? One who learns from every person." — Pirkei Avot 4:1

---

## Symbol Resolution

Resolve symbols by name from any loaded library:

```c
#include "mossad.h"
#include <stdio.h>

void lookup() {
    void *dlopen_addr = MossadSymbolResolver("libdl.so", "dlopen");
    void *malloc_addr = MossadSymbolResolver(NULL, "malloc");

    printf("dlopen @ %p\n", dlopen_addr);
    printf("malloc @ %p\n", malloc_addr);
}
```

> *"לֹא עָלֶיךָ הַמְּלָאכָה לִגְמֹר, וְלֹא אַתָּה בֶן חוֹרִין לְהִבָּטֵל מִמֶּנָּה"*
> "It is not your duty to finish the work, but neither are you free to neglect it." — Pirkei Avot 2:16

---

## Memory Code Patching

Directly patch bytes in memory — for when subtlety gives way to necessity:

```c
#include "mossad.h"

void patch_nop_arm64(void *address) {
    // ARM64 NOP = 0xD503201F
    uint8_t nop[] = {0x1F, 0x20, 0x03, 0xD5};
    MossadCodePatch(address, nop, sizeof(nop));
}
```

> *"הַתּוֹרָה נִתְּנָה בְּמִדְבָּר — מָה מִדְבָּר הֲפְקֵר לַכֹּל, אַף הַתּוֹרָה הֲפְקֵר לַכֹּל"*
> "The Torah was given in the wilderness — just as the wilderness is open to all, so too is the Torah open to all." — Bamidbar Rabbah 1:7

---

## Import Table Replacement (ELF/Mach-O)

Replace a function at the import table level — affects all call sites within a module:

```c
#include "mossad.h"
#include <stdio.h>
#include <string.h>

static ssize_t (*orig_write)(int fd, const void *buf, size_t count);

ssize_t fake_write(int fd, const void *buf, size_t count) {
    if (fd == STDOUT_FILENO) {
        const char *prefix = "[MossadHook] ";
        orig_write(fd, prefix, strlen(prefix));
    }
    return orig_write(fd, buf, count);
}

void install() {
    MossadImportTableReplace(NULL, "write", (void *)fake_write, (void **)&orig_write);
}
```

> *"גַּם זוּ לְטוֹבָה"*
> "This too is for the good." — Taanit 21a

---

## Near Trampoline Configuration

For performance-critical hooks, enable near branch trampolines to avoid long jumps:

```c
#include "mossad.h"

void configure() {
    // Use near branches where possible (ARM/ARM64)
    mossad_set_near_trampoline(true);

    // Or set everything at once
    mossad_set_options(true, NULL);
}
```

> *"אִם אֵין אֲנִי לִי, מִי לִי? וּכְשֶׁאֲנִי לְעַצְמִי, מָה אֲנִי? וְאִם לֹא עַכְשָׁיו, אֵימָתַי?"*
> "If I am not for myself, who will be for me? And when I am only for myself, what am I? And if not now, when?" — Pirkei Avot 1:14

---

## Cleanup

Destroy a hook and restore original code:

```c
#include "mossad.h"

void teardown(void *hooked_address) {
    MossadDestroy(hooked_address);
}
```

> *"כׇּל יִשְׂרָאֵל עֲרֵבִים זֶה בָּזֶה"*
> "All of Israel are responsible for one another." — Shevuot 39a

---

*MossadHook — where others build walls, we build entry points.*
