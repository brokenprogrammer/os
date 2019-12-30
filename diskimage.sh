# Create the disk image
echo "Creating the disk image.."
dd if=/dev/zero of=./hdd.img bs=512 count=1000000

# Partition the disk image
echo "Creating partitions on the disk image.."
(echo o; echo n; echo p; echo 1; echo ; echo; echo t; echo 0c; echo a; echo 1; echo p; echo w) | fdisk -u -C1000 -S63 -H16 ./hdd.img

echo "Disk image was successfully created."