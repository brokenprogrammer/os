#include <stdint.h>

// TODO(Oskar): Magic values, fix me
#define GRAN_64_BIT_MODE (1 << 5)
#define GRAN_32_BIT_MODE (1 << 6)
#define GRAN_4KIB_BLOCKS (1 << 7)

struct tss_entry
{
    uint32_t prev_tss;
    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint16_t trap;
    uint16_t iomap_base;
};

struct tss_entry tss = 
{
    .ss0 = 0x10,
    .esp0 = 0,
    .es = 0x10,
    .cs = 0x08,
    .ds = 0x13,
    .fs = 0x13,
    .gs = 0x13,
};

struct gdt_entry
{
    uint16_t LimitLow;
    uint16_t BaseLow;
    uint8_t BaseMiddle;
    uint8_t Access;
    uint8_t Granularity;
    uint8_t BaseHigh;
};

#define GDT_ENTRY(Base, Limit, Access, Granularity) \
    { (Limit) & 0xFFFF, \
      (Base) >> 0 & 0xFFFF, \
      (Base) >> 16 & 0xFF, \
      (Access) & 0xFF, \
      ((Limit) >> 16 & 0x0F) | ((Granularity) & 0xF0), \
      (Base) >> 24 & 0xFF, \
    }

struct gdt_entry GDT[] =
{
    /* 0x00: Null segment */
    GDT_ENTRY(0, 0, 0, 0),

    /* 0x08: Kernel Code Segment. */
    GDT_ENTRY(0, 0xFFFFFFFF, 0x9A, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

    /* 0x10: Kernel Data Segment. */
    GDT_ENTRY(0, 0xFFFFFFFF, 0x92, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

    /* 0x18: User Code Segment. */
    GDT_ENTRY(0, 0xFFFFFFFF, 0xFA, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

    /* 0x20: User Data Segment. */
    GDT_ENTRY(0, 0xFFFFFFFF, 0xF2, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

    /* 0x28: Task Switch Segment. */
    GDT_ENTRY(0 /*((uintptr_t) &tss)*/, sizeof(tss) - 1, 0xE9, 0x00),
};

uint16_t GDTSizeMinusOne = sizeof(GDT) - 1;