# clear
# echo "Starting OS build..."

# export DRIVE=/dev/loop11
# export PARTITION_OFFSET=2048
# export OS_FOLDER=build

# mkdir -p build

# # TODO(Oskar): Create disk image for building?

# echo "Creating MBR..."
# # Build and install the MBR
# nasm -fbin boot/x86/mbr.s -o build/mbr

# echo "Building bootloader..."
# nasm -fbin boot/x86/stage1.s -o build/stage1
# nasm -fbin boot/x86/stage2.s -o build/stage2

# echo "Compiling the kernel..."

# echo "Complete..."

export DRIVE_RAW=drive
export DRIVE=/dev/loop11
export PARTITION_OFFSET=2048
export OS_FOLDER=os

mkdir -p build
mkdir -p mount
# TODO(Oskar): Create drive file if not exists.

echo "Setting up loop device..."
# Setup the first partition on the drive as the loop device
sudo losetup $DRIVE $DRIVE_RAW -o $((512 * $PARTITION_OFFSET))

echo "Mounting loop device..."
# Mount the loop device

# TODO(Oskar): Make the loop device EXT2 formatted before being able to mount
sudo mkfs -t ext2 $DRIVE

sudo mount $DRIVE mount
sudo chmod 777 mount

echo "Creating MBR..."
# Build and install the MBR
nasm -fbin boot/x86/mbr.s -o build/mbr
sudo dd if=build/mbr of=$DRIVE_RAW bs=436 count=1 conv=notrunc status=none

echo "Installing bootloader..."
# Build and install the bootloader at the start of the partition
nasm -fbin boot/x86/stage1.s -o build/stage1
sudo dd if=build/stage1 of=$DRIVE_RAW bs=512 count=2 conv=notrunc seek=$PARTITION_OFFSET status=none
nasm -fbin boot/x86/stage2.s -o build/$OS_FOLDER/boot

echo "Compiling the kernel..."
# Build and link the kernel
./compile.sh

echo "Creating the bootfsid file..."
# Create a bootfsid file
echo -n 1234 > build/os/bootfsid

# echo "Copying the files to the drive..."
# # Copy the bin directory to the mount
# cp -r bin/* mount/

echo "Unmounting the loop device..."
# Unmount the loop device
sudo umount $DRIVE
sudo losetup --detach $DRIVE

echo "Build successful."