!/bin/bash

cd /root/cs350-os161/os161-1.99/kern/conf

./config ASST0

cd ../compile/ASST0

bmake depend
bmake
bmake install


# Building OS161 user level utilities and test programs (need to be done if changes in the test programs are made)

cd /root/cs350-os161/os161-1.99

bmake
bmake install


# Running the kernel

cd /root/cs350-os161/root
exec bash
# sys161 kernel-ASST0 #execute/run the kernel
