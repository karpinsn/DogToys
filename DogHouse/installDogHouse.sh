#~/bin/bash

if [ $# = 0 ]; then
    sudo ./setup_sdcard.sh --probe-mmc
    echo "Find where the sd card is mounted. It should be like /dev/sdb"
    echo "rerun this script passing the variable in"
    exit
fi

echo "Writing the image to the sd card ..."
sudo ./setup_sdcard.sh --mmc $1 --uboot bone
