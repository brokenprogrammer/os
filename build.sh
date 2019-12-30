clear

export DRIVE_RAW=hdd.img
export DRIVE=/dev/loop11
export PARTITION_OFFSET=2048
export OS_FOLDER=os

mkdir -p build
sleep 0.5s
mkdir -p build/os
sleep 0.5s
# mkdir -p mount

echo "Setting up loop device..."
# Setup the first partition on the drive as the loop device
sudo losetup $DRIVE $DRIVE_RAW -o $((512 * $PARTITION_OFFSET))
sleep 0.5s

echo "Formatting the loop device to ext2..."
sudo mke2fs -F $DRIVE
sleep 0.5s

echo "Mounting loop device..."
# Mount the loop device
sudo mount -t ext2 $DRIVE mount
sudo chmod 777 mount
sudo chmod 777 build
sudo chmod 777 $DRIVE_RAW
sleep 0.5s

echo "Creating MBR..."
# Build and install the MBR
nasm -fbin boot/x86/mbr.s -o build/mbr
sudo dd if=build/mbr of=$DRIVE_RAW bs=446 count=1 conv=notrunc status=none

echo "Installing bootloader..."
# Build and install the bootloader at the start of the partition
nasm -fbin boot/x86/stage1.s -o build/stage1
sudo dd if=build/stage1 of=$DRIVE_RAW bs=512 count=2 conv=notrunc seek=$PARTITION_OFFSET status=none
nasm -fbin boot/x86/stage2.s -o build/$OS_FOLDER/boot

echo "Compiling the kernel..."
# Build and link the kernel
# ./compile.sh

echo "Creating the bootfsid file..."
# Create a bootfsid file
echo -n 1234 > build/os/bootfsid
sleep 1.0s

echo "Copying the files to the drive..."
# Copy the bin directory to the mount
sudo cp -r build/* mount
sleep 0.5s

echo "Unmounting the loop device..."
# Unmount the loop device
sudo umount $DRIVE
sudo losetup --detach $DRIVE

echo "Build successful."