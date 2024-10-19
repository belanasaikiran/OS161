# OS161

### Labs

1. LAB1: Alternative to installing VirtualBox on MAC M1/M2/M3

Posted on: Tuesday, September 10, 2024 4:38:32 PM EDT

Hi All,

As some of the students with MAC machines indicated facing issue installing Virtualbox on their machine, An alternative approach could be to setup a Docker environment that comes with OS161 installed. To do that, please install Docker (https://www.docker.com) on your machine and follow the steps from this Github link - https://github.com/Uberi/uw-cs350-development-environment/tree/master

Once you install Docker on your machine, you should follow the steps from the "Usage" specified in the Github README (from 'If you are not on Debian/Ubuntu'). 

For building the kernel, please use the following code (instead of the build-and-run-kernel.sh if you face issue with it) -

```bash
mkdir --parents /root/cs350-os161/root
cp --update /root/sys161/share/examples/sys161/sys161.conf.sample /root/cs350-os161/root/sys161.conf

cd /root/cs350-os161/os161-1.99
./configure --ostree=/root/cs350-os161/root --toolprefix=cs350-

cd /root/cs350-os161/os161-1.99/kern/conf
./config ASST0

cd /root/cs350-os161/os161-1.99/kern/compile/ASST0

bmake depend
bmake
bmake install


cd /root/cs350-os161/os161-1.99
bmake
bmake install

```

To run the kernel:

```bash
cd /root/cs350-os161/root
sys161 kernel-ASST0
```


2. [Lab 2](./Labs/lab2.md)

3. [Lab 3 Report](./Labs/Lab3/Lab3_Report.md)



## External References:

1. [Adding System Calls](https://cs.fit.edu/~eribeiro/teaching/cse4001/addsystemcalls.pdf)

2. [System Calls](https://ops-class.org/asst/2/)
