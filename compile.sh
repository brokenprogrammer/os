i686-elf-as kernel/interrupt.s -o build/interrupt
i686-elf-gcc -c kernel/gdt.c -o build/gdt -std=gnu99 -ffreestanding -DARCH_64 -DARCH_X86_64 -DARCH_X86_COMMON -O2 -Wall -Wextra
i686-elf-gcc -c kernel/kernel.c -o build/kernel -std=gnu99 -ffreestanding -DARCH_64 -DARCH_X86_64 -DARCH_X86_COMMON -O2 -Wall -Wextra

cd build

i686-elf-gcc -T ../linker.ld -o os.out -ffreestanding -O2 -nostdlib interrupt gdt kernel -lgcc -g -mno-red-zone -z max-page-size=0x1000

cd ..