#~/bin/bash

filename="ubuntu-12.04-r1-minimal-armhf.tar.xz"

echo "Downloading files ..."
wget http://rcn-ee.net/deb/rootfs/precise/$filename
echo "Files downloaded"

correctHash='28a2e3969f3d6dd434d2481fd443e634' 
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


