#!/bin/bash


cd /root/cs350-os161/os161-1.99
./configure --ostree=/root/cs350-os161/root --toolprefix=cs350-


cd /root/cs350-os161/os161-1.99/kern/conf

./config ASST1

cd ../compile/ASST1
bmake clean
bmake depend
bmake
bmake install


# Building OS161 user level utilities and test programs (need to be done if changes in the test programs are made)

cd /root/cs350-os161/os161-1.99

bmake
bmake install


# Running the kernel

cd /root/cs350-os161/root
#exec bash
sys161 kernel-ASST1 #execute/run the kernel
