// NOTE(Oskar): Kernel Heap helper functions. This is a replacement for malloc
//              used before the heap is fully initialized.

extern u32 end; // NOTE(Oskar): Defined in linker.ld.
u32 PlacementAddress = (u32)&end;


// TODO(Oskar): This should later be placed somewhere else.
u32 kmalloc(u32 AllocationSize, s32 Align, u32 *PhysicalAddress)
{
    // NOTE(Oskar): If the address is not already page-aligned then we align it.
    if (Align == 1 && (PlacementAddress & 0xFFFFF000))
    {
        PlacementAddress &= 0xFFFFF000;
        PlacementAddress += 0x1000;
    }

    if (PhysicalAddress)
    {
        *PhysicalAddress = PlacementAddress;
    }

    u32 Temp = PlacementAddress;
    PlacementAddress += AllocationSize;
    return (Temp);
}