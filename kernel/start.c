// include, 
// kernel
// protected_mode
// ..

void cstart(cs, ds, mds, parmoff, parmsize)
u16 cs, ds;
u16 mds;
u16 parmoff, parmsize;
{
    char params[128 * sizeof(char *)];
    register char *value;
    extern int etext, end;

    // TODO(Oskar)
}