#~/bin/bash

filename="ubuntu-12.04-preinstalled-desktop-armhf+omap.img.gz"

echo "Downloading files ..."
wget http://cdimage.ubuntu.com/releases/12.04/release/$filename
echo "Files downloaded"

correctHash='3d14124427a8b7c23c193b30152b0d92' 
fileHash=$(md5sum $filename | awk '{print $1}')

if [ $correctHash != $fileHash ]; then
    echo "The hashes do not match. Try rerunning the script"
    echo "Expected hash: " $correctHash
    echo "Actual hash: " $fileHash
    exit
fi

echo "Unpacking the image ..."
tar xJf $filename 
echo "Copying next install script"
cp installDogHouse.sh ./${filename%.tar.xz}
echo "Removing temporary files"
rm $filename
