CVE-2021-3656:

This issue is caused by missing validation of the the `virt_ext` VMCB
field and allows a malicious L1 guest to disable both VMLOAD/VMSAVE
intercepts and VLS (Virtual VMLOAD/VMSAVE) for the L2 guest. Under
these circumstances, the L2 guest is able to run VMLOAD/VMSAVE
unintercepted, and thus read/write portions of the host physical
memory.


Setup Environment to access Linux Kernel:
1. You could use a Docker container or use a Virtual Machine. I will do my best with a
docker container

2. You want to have Docker Desktop setup on MAC or Windows. If you have a Linux
machine by default, you can ignore all these steps.

3. Next you want to pull an ubuntu image from:[ ubuntu - Official Image | Docker Hub](url)

a. For Windows you can type “docker pull ubuntu” in PowerShell or CMD

b. Same for MAC
i. Note: This will pull the latest version of ubuntu. You may want to pull an
older version so you could have a older version of its kernel
ii. Create a directory with a Dockerfile in it. The file at bare minimum needs
to have: “From ubuntu:16.04”
iii. To get an older version type: “docker build -t ubuntu-xenial” for example
iv. To check your current images type: “docker image ls”

c. Once you run the command from iii, the system will provide you with a container
ID.
i. You can check “docker container ls” to make sure the container is
available

d. Moving up to access this container you are going to want to type: “docker exec -it
<NAMES> <COMMAND>”

e. You should now be in your container in the directory “/”

f. This exploit was found in kernel version 4.13; we need to make sure that is the
version that our workplace is running
i. To check type: uname -r

g. From here you find the kernel directory by typing: “cd sys/kernel”

h. From here I did not make much progress since I could not find a way to
downgrade to kernel 4.13

i. I also tried downgrading using virtual machines, but that did not work
either


References:

● oss-security - [[CVE-2021-3653, CVE-2021-3656] SVM nested virtualization issues in
KVM (openwall.com)](url)
○ This is an overview of two vulnerabilities that were found in the KVM’s AMD code
for supported nested virtualization

● This is the patch: [kvm/kvm.git - kernel-based virtual machine - kvm](url)

● KVM: SVM: [Enable Virtual VMLOAD VMSAVE feature · torvalds/linux@89c8a49
(github.com)](url)
○ This is the vulnerable code

● [RHSA-2021:3676 - Security Advisory - Red Hat Customer Portal](url)

● [CVE-2021-3656- Red Hat Customer Portal](url)
○ Red Hat description of the exploit

●[ 1983988 – (CVE-2021-3656) CVE-2021-3656 kernel: SVM nested virtualization issue in](url)
KVM (VMLOAD/VMSAVE) (redhat.com)

● [What is KVM? (redhat.com)](url)
○ Explanation on what a KVM is

● [How to Check Linux Kernel Version in Command Line (4 Easy Options)
(phoenixnap.com)](url)

● How to downgrade the Linux kernel articles and videos
○ How to Downgrade the Kernel in Linux - Make Tech Easier
○ How to Downgrade from WSL Version 2 to WSL Version 1 - MSSQL DBA Blog
(peter-whyte.com)
○ Linux Series - 2.1.5 Upgrading/Downgrading the Linux Kernel - YouTube

● How to check KVM is installed in Ubuntu Linux - Linux Shout (how2shout.com)
○ Need to have KVM for this exploit

● How to install QEMU/KVM on Ubuntu 22.04 | 20.04 LTS - Linux Shout (how2shout.com)

● How To Install Linux Kernel 4.13 In Ubuntu And Linux Mint? (fossbytes.com)
○ How to install the Linux Kernel 4.13
