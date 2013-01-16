#!/bin/bash

sudo losetup /dev/loop0 floppy.img
sudo bochs -f bochsrc
sudo losetup -d /dev/loop0
