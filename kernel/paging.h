#ifndef PAGING_H
#define PAGING_H

typedef struct page_t
{
    u32 Present;    // NOTE(Oskar): Present in memory.
    u32 RW;         // NOTE(Oskar): Read-only if clear, ReadWrite if set.
    u32 User;       // NOTE(Oskar): Supervisor level only if clear.
    u32 Accessed;   // NOTE(Oskar): If page has been accessed since last refresh.
    u32 Dirty;      // NOTE(Oskar): If page has been written to since last refresh.
    u32 Unused;     // NOTE(Oskar): Unused and reserved bits.
    u32 Frame;      // NOTE(Oskar): Frame address.
} page;

typedef struct page_table_t
{
    page Pages[1024];
} page_table;

typedef struct page_directory_t
{
    page_table *Tables[1024];
    u32 TablePhysicalLocation[1024];    // NOTE(Oskar): Physical address to above page tables.
    u32 PhysicalAddress;                // NOTE(Oskar): Physical address of above physical addresses.
} page_directory;

#endif // PAGING_H