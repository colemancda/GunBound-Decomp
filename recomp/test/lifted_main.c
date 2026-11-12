/* Lifted harness: runs the lifted snippets on the recompilation runtime and
 * prints the same report as the native reference (ref_main.c).
 *
 *   lifted_test <snippets.bin> [-v]
 */
#include <stdio.h>
#include <stdlib.h>

#include "rt.h"
#include "tests.h"

static GuestFn fns[N_TESTS];
static CPU cpu;
static uint32_t out_buf;
static int failures;

void put_str(const char *s) { fputs(s, stdout); }

void test_call(int index, u32 a, u32 b, u32 cc, u32 d, u32 out[8]) {
    CPU *c = &cpu;
    const uint32_t sp0 = GUEST_STACK_TOP - 0x1000;
    memset(G(out_buf), 0, 32);
    ESP = sp0;
    PUSH32(out_buf);
    PUSH32(d);
    PUSH32(cc);
    PUSH32(b);
    PUSH32(a);
    PUSH32(GUEST_EXIT_ADDR);
    EBX = 0xB0B0B0B0u;
    ESI = 0x51515151u;
    EDI = 0xD1D1D1D1u;
    EBP = 0xB9B9B9B9u;
    fns[index](c);
    /* cdecl contract: returned to us, arguments still on the stack, callee-saved
     * registers intact, direction flag clear, x87 stack empty. */
    if (c->eip != GUEST_EXIT_ADDR || ESP != sp0 - 20 || EBX != 0xB0B0B0B0u || ESI != 0x51515151u ||
        EDI != 0xD1D1D1D1u || EBP != 0xB9B9B9B9u || c->df || c->ftop != 0) {
        if (failures++ < 10)
            fprintf(stderr, "%s: calling convention violated (eip=%08x esp=%08x ebx=%08x esi=%08x edi=%08x ebp=%08x df=%u ftop=%u)\n",
                    test_descs[index].name, c->eip, ESP, EBX, ESI, EDI, EBP, c->df, c->ftop);
    }
    memcpy(out, G(out_buf), 32);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s snippets.bin [-v]\n", argv[0]);
        return 2;
    }
    rt_mem_init();
    rt_build_ftab();

    /* The blob must be in guest memory: jump tables are read from it at run time. */
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror(argv[1]);
        return 2;
    }
    rt_mem_commit(rt_text_base, rt_text_size);
    if (fread(G(rt_text_base), 1, rt_text_size, f) != rt_text_size) {
        fprintf(stderr, "%s: short read\n", argv[1]);
        return 2;
    }
    fclose(f);

    for (int i = 0; i < N_TESTS; i++) {
        for (uint32_t k = 0; k < rt_nfuncs; k++)
            if (!strcmp(rt_funcs[k].name, test_descs[i].name)) fns[i] = rt_funcs[k].fn;
        if (!fns[i]) {
            fprintf(stderr, "snippet %s was not lifted\n", test_descs[i].name);
            return 2;
        }
    }

    rt_set_cpu(&cpu);
    cpu.fcw = 0x27F;
    out_buf = rt_sys_alloc(64);
    run_tests(argc > 2);
    fflush(stdout);
    if (failures) {
        fprintf(stderr, "%d calls violated the calling convention\n", failures);
        return 1;
    }
    return 0;
}
