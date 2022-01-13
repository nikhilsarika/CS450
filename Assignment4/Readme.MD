# CS450-Assignment4

Changes are made to fs.c to implement the requirements.

Methods Implemented in fs.c:
  1. directoryWalker(char *path) : This is method implemented to print all the files and directories in a ginven path. The path is an optional paramter and by default it takes the root path 
  2. inodeTBWalker(void) : This method prints all the inode values in the inode Table
  3. compareWalker(void) : This method compares the inodeWalker with the direcotryWalker and prints the inode values of the missing inodes. 
  4. damageInode(int inum) : This method is used to unlink the inode from its directory. This way the directoryWalker will not be able to print the inode number but we can see the inode number with the help of damageInode method. 
  5. recoverFile(void) : This method compares the outputs from inode walker and direcory walker and recovers the missing inodes from cache and relinks it to the directory. 

Systems Calls Implemented: 
  1. All 5 methods implemented above are made available to user in the form of system calls. 5 system calls are implemented with necessary changes in user.h, usys.S, syscall.c, syscall.h and sysproc.c files. 

Test Classes Implemented: 
  1. directoryWalkerTest.c : This file tests the directoryWalker system call. This prints all the files in the path provided and their inode numbers.
  2. inodeWalkerTest.c: This file tests the inodeTBWalker system call. This prints all the inodes the are availble in the inode table.
  3. compareWalkerTest.c : This file tests compareWalker system call. This prints the inode value that is damaged. 
  4. damageInodeTest.c : This file tests the damageInode system call. This prints "Damged Inode" on successfull delinking of a indoe from its directory.
  5. recoverFile.c: This file tests the recoverFile system call. This prints all recovered inode numbers.

Build Instructions: 
  1. Open the xv6 directory in a linux machine. 
  2. Run the command : make clean  This will clear the existing image of the operating system  
  3. Run the command : make qemu-nox. This will recompile all the files and starts the operating system. 

Testing the Implementation: 
  The Makefile is modified to include all the testfiles implemeted. The test files are to be excuted in the following order. 
  1. directoryWalkerTest : ![image](https://user-images.githubusercontent.com/45618814/144322237-c3e9dcc2-d1c9-4d8c-846e-68d0f5d7058f.png)
  2. inodeWalkerTest 
  3. compareWalkerTest 
  4. Creaate two directories to test the damage and recoveFile systemcalls. 1. mkdir testDir 2. mkdir testDir/nestedDir
  5. damageInodeTest 24 (24 is the inode value of the newly created directory in the above step).
  6. compareWalkerTest 
  7. recoverFile