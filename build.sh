clear
echo "Starting OS build..."

export DRIVE=/dev/loop11
export PARTITION_OFFSET=2048
export OS_FOLDER=build

mkdir -p build

# TODO(Oskar): Create disk image for building?

echo "Creating MBR..."
# Build and install the MBR
nasm -fbin boot/x86/mbr.s -o build/mbr

echo "Building bootloader..."
nasm -fbin boot/x86/stage1.s -o build/stage1
nasm -fbin boot/x86/stage2.s -o build/stage2

echo "Compiling the kernel..."

echo "Complete..."