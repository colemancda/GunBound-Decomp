/* Fake COM objects for the DirectX modules.
 *
 * An object the guest sees is a small block of guest memory: a pointer to a
 * vtable (also in guest memory) whose slots are host-function addresses, then
 * the index of the host-side state. Methods that have no implementation are
 * stubs that stop the program with the interface and method name.
 */
#ifndef RECOMP_COM_H
#define RECOMP_COM_H

#include "rt.h"

typedef struct ComMethod {
    const char *name;
    ImportFn fn; /* NULL: stops with "UNIMPLEMENTED" when called */
    int nargs;   /* including `this` */
} ComMethod;

/* Guest address of a vtable for the methods; built once per table. */
uint32_t rt_com_vtable(const char *dll, const char *iface, const ComMethod *methods, unsigned count);
/* New guest object {vtable, index, magic}. */
uint32_t rt_com_object(uint32_t vtable, uint32_t index, uint32_t magic);
/* Host index of a guest object, or -1 if it is not an object of that kind. */
int rt_com_index(uint32_t obj, uint32_t magic);
void rt_com_free(uint32_t obj);

#define S_OK 0u
#define E_NOTIMPL 0x80004001u
#define E_NOINTERFACE 0x80004002u
#define E_POINTER 0x80004003u
#define E_FAIL 0x80004005u
#define E_INVALIDARG 0x80070057u
#define E_OUTOFMEMORY 0x8007000Eu

/* "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}" for a GUID in guest memory. */
const char *rt_guid_str(uint32_t guid, char buf[40]);
int rt_guid_eq(uint32_t guid, const uint8_t ref[16]);

/* Scratch space below the guest stack pointer for structures passed to guest
 * callbacks. Usage: uint32_t sp = ESP; uint32_t p = rt_stack_alloc(c, n); ...; ESP = sp; */
static inline uint32_t rt_stack_alloc(CPU *c, uint32_t size) {
    uint32_t p = (ESP - size) & ~15u;
    ESP = p - 16;
    return p;
}

#endif
